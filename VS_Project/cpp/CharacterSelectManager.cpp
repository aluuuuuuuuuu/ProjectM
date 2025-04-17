#include "CharacterSelectManager.h"
#include "SelectFinger.h"
#include "CharacterCard.h"
#include "Input.h"
#include "SoundManager.h"

CharacterSelectManager::CharacterSelectManager(PlayerData& plData) :
	_plData(plData),
	_selectFinishFlag(false),
	_pushStart(false),
	_returnFlag(false),
	_startButtonHandle(0),
	_viewStartButtonFlag(false)
{
	// �萔�̃t�@�C����ǂݍ���
	ReadCSV("data/constant/CharactorSelectManager.csv");

	// �w�̃C���X�^���X��l�����쐬����
	for (int i = 0; i <= _plData.playerNum; i++) {
		_pFinger[i] = std::make_shared<SelectFinger>(i);
	}

	// �J�[�h�̃C���X�^���X���L�����N�^�[���쐬����
	for (int i = 0; i < GetConstantInt("CHARACTOR_NUM"); i++) {
		_pCard[i] = std::make_shared<CharacterCard>(i);
	}

	// �X�^�[�g�摜�̃��[�h
	_startButtonHandle = LoadGraph("data/image/ReadyFight.png");
	_startButtonPos = Vec2{ GetConstantFloat("START_BUTTON_POS_X"),GetConstantFloat("START_BUTTON_POS_Y") };
}

CharacterSelectManager::~CharacterSelectManager()
{
	DeleteGraph(_startButtonHandle);
}

void CharacterSelectManager::Update()
{
	// �S�w�̍X�V����
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Update();
	}

	// �w�ƃJ�[�h�̔�����Ƃ�
	FingerFunction();

	// �S�w���I�����I����������肷��
	_selectFinishFlag = true;
	for (int num = 0; num <= _plData.playerNum; num++) {
		if (!_pFinger[num]->IsSelected()) {
			_selectFinishFlag = false;
			break;
		}
	}

	// �X�^�[�g�{�^�����X���C�h�C���E�A�E�g������
	if (_selectFinishFlag) {
		_viewStartButtonFlag = true;
		if (_startButtonPos.y > GetConstantFloat("START_BUTTON_POS_X")) {
			_startButtonPos.y -= GetConstantFloat("START_BUTTON_MOVE_SCALE");
			if (_startButtonPos.y < GetConstantFloat("START_BUTTON_POS_X")) {
				_startButtonPos.y = GetConstantFloat("START_BUTTON_POS_X");
			}
		}
	}
	else {
		if (GetConstantFloat("START_BUTTON_POS_Y") >= _startButtonPos.y) {
			_startButtonPos.y += GetConstantFloat("START_BUTTON_MOVE_SCALE");
		}
		else {
			_viewStartButtonFlag = false;
		}
	}
}

void CharacterSelectManager::Draw() const
{
	// �S�J�[�h�̕`��
	for (auto& card : _pCard) {
		card->Draw();
	}

	// �I�����I����Ă�����X�^�[�g�{�^����\������
	if (_viewStartButtonFlag) {
		DrawRotaGraph(_startButtonPos.intX(), _startButtonPos.intY(), 1.0, 0.0, _startButtonHandle, true);
	}

	// �S�w�̕`��
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}
}

bool CharacterSelectManager::GetStart() const
{
	return _pushStart;
}

void CharacterSelectManager::CreateData()
{
	for (int num = 0; num <= _plData.playerNum; num++) {
		_plData.character[num] = _pFinger[num]->GetSelectChara();
	}
}

bool CharacterSelectManager::GetReturnFlag()
{
	return _returnFlag;
}

void CharacterSelectManager::FingerFunction()
{
	for (int num = 0; num <= _plData.playerNum; num++) {

		// A�{�^�����������Ƃ��̏���
		if (_pFinger[num]->IsPushButton(INPUT_A)) {
			for (auto& card : _pCard) {
				// �܂��I�����Ă��炸�A�I������Ă��Ȃ��J�[�h�Əd�Ȃ��Ă�����I������
				if (IsFingerOnCard(_pFinger[num], card) && !card->GetSelectFlag() && !_pFinger[num]->IsSelected()) {
					card->SelectCharacter(_pFinger[num]->GetPadNum());
					_pFinger[num]->SetSelectFlag(true);
					_pFinger[num]->SetSelectChara(card->GetCharacterNum());

					// �L�����I������炷
					SoundManager::GetInstance().RingSE(SE_CHARA_SELECT);
				}
			}

			// �I���I�����Ă����Ƃ��Ɏw���X�^�[�g�{�^���ɏd�Ȃ��Ă�����Q�[���X�^�[�g�������s��
			if (_selectFinishFlag) {
				if (_pFinger[num]->GetPos().x > _startButtonPos.x - GetConstantFloat("CARD_WIDTH") &&
					_pFinger[num]->GetPos().x < _startButtonPos.x + GetConstantFloat("CARD_WIDTH") &&
					_pFinger[num]->GetPos().y > _startButtonPos.y - GetConstantFloat("CARD_HEIGHT") &&
					_pFinger[num]->GetPos().y < _startButtonPos.y + GetConstantFloat("CARD_HEIGHT")) {
					_pushStart = true;

					// �Q�[���X�^�[�g����炷
					SoundManager::GetInstance().RingSE(SE_GAME_START);
				}
			}
		}

		// B�{�^�����������Ƃ��̏���
		if (_pFinger[num]->IsPushButton(INPUT_B)) {
			// �I�����Ă�����I������������
			if (_pFinger[num]->IsSelected()) {
				_pCard[_pFinger[num]->GetSelectChara()]->RejectCharacter(num);
				_pFinger[num]->SetSelectFlag(false);

				// �L�����Z������炷
				SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);
			}
			// �I�����Ă��Ȃ�������l���I���ɖ߂�
			else {
				_returnFlag = true;
			}

		}
	}
}

bool CharacterSelectManager::IsFingerOnCard(std::shared_ptr<SelectFinger>& fing, std::shared_ptr<CharacterCard>& card)
{
	// ���ꂼ��̍��W���擾
	Vec2 fingPos = fing->GetPos();
	Vec2 cardPos = Vec2{ card->GetPos().x + GetConstantFloat("CARD_MARGIN"),card->GetPos().y + GetConstantFloat("CARD_MARGIN") };

	// finger���J�[�h�̏�ɂ��邩����
	if (fingPos.x >= cardPos.x &&
		fingPos.x <= cardPos.x + card->GetConstantInt("CARD_SIZE_WIDTH") &&
		fingPos.y >= cardPos.y &&
		fingPos.y <= cardPos.y + card->GetConstantInt("CARD_SIZE_HEIGHT")) {

		return true;
	}
	return false;
}

#include "CharactorSelectManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "Vec2.h"
#include "Input.h"

CharactorSelectManager::CharactorSelectManager(PlayerData& plData) :
	_plData(plData),
	_selectFinishFlag(false),
	_pushStart(false)
{
	// �w�̃C���X�^���X��l�����쐬����
	for (int i = 0; i <= _plData.playerNum; i++) {
		_pFinger[i] = std::make_shared<SelectFinger>(i);
	}

	// �J�[�h�̃C���X�^���X���L�����N�^�[���쐬����
	for (int i = 0; i < 4; i++) {
		_pCard[i] = std::make_shared<CharactorCard>(i);
	}
}

CharactorSelectManager::~CharactorSelectManager()
{
}

void CharactorSelectManager::Update()
{

	// �S�w�̍X�V����
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Update();
	}

	// �S�J�[�h�̕`��
	for (auto& card : _pCard) {
		card->Draw();
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

	// �I�яI�������ɉ��\�����Ă���~�̏��A�{�^������������Q�[�����J�n�����
	if (_selectFinishFlag && Input::GetInstance().IsTrigger(INPUT_A,INPUT_PAD_1)) {
		if ((_pFinger[0]->GetPos() - Vec2{ 600,600 }).Length() <= 200) {
			_pushStart = true;
		}
	}
}

void CharactorSelectManager::Draw() const
{
	// �S�J�[�h�̕`��
	for (auto& card : _pCard) {
		card->Draw();
	}

	// �S�w�̕`��
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}

	// �I�����I����Ă����牽����\������
	if (_selectFinishFlag) {
		DrawCircle(600, 600, 200, 0xff0000);
	}
}

bool CharactorSelectManager::GetStart() const
{
	return _pushStart;
}

void CharactorSelectManager::CreateData()
{
	for (int num = 0; num <= _plData.playerNum; num++) {
		_plData.charactor[num] = _pFinger[num]->GetSelectChara();
	}
}

void CharactorSelectManager::FingerFunction()
{
	for (int num = 0; num <= _plData.playerNum; num++) {

		// A�{�^�����������Ƃ��̏���
		if (_pFinger[num]->IsPushButton(INPUT_A)) {
			for (auto& card : _pCard) {
				// �܂��I�����Ă��炸�A�I������Ă��Ȃ��J�[�h�Əd�Ȃ��Ă�����I������
				if (IsFingerOnCard(_pFinger[num], card) && !card->GetSelectFlag() && !_pFinger[num]->IsSelected()) {
					card->SelectCharactor(_pFinger[num]->GetPadNum());
					_pFinger[num]->SetSelectFlag(true);
					_pFinger[num]->SetSelectChara(card->GetCharactorNum());
				}
			}
		}

		// B�{�^�����������Ƃ��̏���
		if (_pFinger[num]->IsPushButton(INPUT_B)) {
			for (auto& card : _pCard) {
				// �I�����Ă��āA�Ώۂ̎w���I�������J�[�h�Əd�Ȃ��Ă�����I����������
				if (card->GetSelectFlag(num)) {
					_pFinger[num]->SetSelectFlag(false);
					_pCard[_pFinger[num]->GetSelectChara() - 1]->RejectCharactor(num);
				}
			}
		}
	}
}

bool CharactorSelectManager::IsFingerOnCard(std::shared_ptr<SelectFinger>& fing, std::shared_ptr<CharactorCard>& card)
{
	// ���ꂼ��̍��W���擾
	Vec2 fingPos = fing->GetPos();
	Vec2 cardPos = Vec2{ card->GetPos().x + 10.0f,card->GetPos().y + 10.0f };

	// finger���J�[�h�̏�ɂ��邩����
	if (fingPos.x >= cardPos.x &&
		fingPos.x <= cardPos.x + card->GetConstantInt("CARD_SIZE_WIDTH") &&
		fingPos.y >= cardPos.y &&
		fingPos.y <= cardPos.y + card->GetConstantInt("CARD_SIZE_HEIGHT")) {

		return true;
	}
	return false;
}

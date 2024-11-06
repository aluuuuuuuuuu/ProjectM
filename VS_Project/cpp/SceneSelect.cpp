#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"

SceneSelect::SceneSelect():
	_flame(60)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeDraw;

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(1, 512);

	for (auto& select : _finishSelect) {
		select = false;
	}

	// �ŏ��̐l���͂��Ȃ炸��l
	_plData.playerNum = 1;


	back = LoadGraph("data/image/back.jpg");
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::PlayerNumSelectUpdate()
{
	// B�{�^���Ől���̐؂�ւ�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_plData.playerNum == Input::GetInstance().GetPadNum()) {
			_plData.playerNum = 1;
		}
		else {
			_plData.playerNum++;
		}
	}

	// A�{�^���Ŏ��̉�ʂ�
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// �w�̃C���X�^���X��l�����쐬����
		for (int i = 0; i < _plData.playerNum; i++) {
			_pFinger[i] = std::make_shared<SelectFinger>(i);
		} 
		
		// �J�[�h�̃C���X�^���X���L�����N�^�[���쐬����
		for (int i = 0; i < 4; i++) {
			_pCard[i] = std::make_shared<CharactorCard>(i + 1);
		}

		// �L�����N�^�[�I���Ɉڍs
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
	}
}

void SceneSelect::PlayerNumSelectDraw() const
{
	switch (_plData.playerNum)
	{
	case 1:
		DrawFormatString(10, 10, 0xffffff, "1�l");
		break;
	case 2:
		DrawFormatString(10, 30, 0xffffff, "2�l");
		break;
	case 3:
		DrawFormatString(10, 50, 0xffffff, "3�l");
		break;
	case 4:
		DrawFormatString(10, 70, 0xffffff, "4�l");
		break;
	default:
		break;
	}

	DrawCircle(800, 400, 200, 0x000000);
}

void SceneSelect::CharactorSelectUpdate()
{
	// �S�w�̍X�V����
	for (int num = 0; num < _plData.playerNum; num++) {
		_pFinger[num]->Update();
	}
}

void SceneSelect::CharactorSelectDraw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, back,true);

	// �S�J�[�h�̕`��
	for (auto& card : _pCard) {
		card->Draw();
	}

	// �S�w�̕`��
	for (int num = 0; num < _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::PlayerNumSelectUpdate;
		_drawFunc = &SceneSelect::PlayerNumSelectDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_plData));
	}
}

void SceneSelect::FadeDraw() const
{
	DrawCircle(800, 400, 200, 0x000000);

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

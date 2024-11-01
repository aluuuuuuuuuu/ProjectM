#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"

SceneSelect::SceneSelect():
	_flame(60),
	_playerNum(1)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeDraw;

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(1, 512);
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
	// B�{�^���ł��낢��؂�ւ�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_playerNum == Input::GetInstance().GetPadNum()) {
			_playerNum = 1;
		}
		else {
			_playerNum++;
		}
	}

	// A�{�^���Ŏ��̉�ʂ�
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		// �t�F�[�h�A�E�g�ֈڍs
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
	}
}

void SceneSelect::PlayerNumSelectDraw() const
{
	switch (_playerNum)
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
	for (int i = 0; i < _playerNum; i++) {

	}

}

void SceneSelect::CharactorSelectDraw() const
{
	DrawCircle(100, 100, 100, 0xffffff, true);
	DrawCircle(100, 500, 100, 0xffffff, true);
	DrawCircle(500, 100, 100, 0xffffff, true);
	DrawCircle(500, 500, 100, 0xffffff, true);
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
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerNum));
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

#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"

SceneSelect::SceneSelect():
	_flame(60),
	_select(1)
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

void SceneSelect::NormalUpdate()
{
	// B�{�^���ł��낢��؂�ւ�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_select == 4) {
			_select = 1;
		}
		else {
			_select++;
		}
	}



	// A�{�^���Ŏ��̉�ʂ�
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		// �t�F�[�h�A�E�g�ֈڍs
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeDraw;
	}
}

void SceneSelect::NormalDraw() const
{
	switch (_select)
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

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::NormalUpdate;
		_drawFunc = &SceneSelect::NormalDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_select));
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

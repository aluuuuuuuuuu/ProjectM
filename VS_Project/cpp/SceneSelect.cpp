#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"

SceneSelect::SceneSelect():
	_flame(60),
	_select(1)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeDraw;

	// カメラのニアファーの設定
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
	// Bボタンでいろいろ切り替え
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_select == 4) {
			_select = 1;
		}
		else {
			_select++;
		}
	}



	// Aボタンで次の画面へ
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		// フェードアウトへ移行
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeDraw;
	}
}

void SceneSelect::NormalDraw() const
{
	switch (_select)
	{
	case 1:
		DrawFormatString(10, 10, 0xffffff, "1人");
		break;
	case 2:
		DrawFormatString(10, 30, 0xffffff, "2人");
		break;
	case 3:
		DrawFormatString(10, 50, 0xffffff, "3人");
		break;
	case 4:
		DrawFormatString(10, 70, 0xffffff, "4人");
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

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

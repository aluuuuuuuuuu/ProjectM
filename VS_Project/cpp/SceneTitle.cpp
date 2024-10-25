#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"

SceneTitle::SceneTitle():
	_flame(60)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneTitle::FadeInUpdate;
	_drawFunc = &SceneTitle::FadeDraw;

	// カメラのニアファーの設定
	SetCameraNearFar(1, 512);

	// タイトルロゴのロード
	_logoHandle = LoadGraph("data/image/TitleLogo.png");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_logoHandle);
}

void SceneTitle::Update()
{
	(this->*_updateFunc)();
}

void SceneTitle::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTitle::NormalUpdate()
{
	// Aボタンで次の画面へ
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		// フェードアウトへ移行
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}
}

void SceneTitle::NormalDraw() const
{
	// ロゴの描画
	DrawGraph(200, 100, _logoHandle, true);
}

void SceneTitle::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{

	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>());
	}
}

void SceneTitle::FadeDraw() const
{
	// ロゴの描画
	DrawGraph(200, 100, _logoHandle, true);

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

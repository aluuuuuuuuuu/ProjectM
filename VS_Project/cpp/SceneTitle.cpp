#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"
#include "Application.h"
#include "SoundManager.h"
#include "Crown.h"

SceneTitle::SceneTitle() :
	_flame(110)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneTitle::FadeInUpdate;
	_drawFunc = &SceneTitle::FadeDraw;

	// 王冠インスタンスの作成
	_pCrown = std::make_shared<Crown>();

	// カメラのニアファーの設定
	SetCameraNearFar(1, 512);

	// タイトルロゴのロード
	_logoHandle = LoadGraph("data/image/TitleLogo.png");

	// anybutton画像のロード
	_guideHandle = LoadGraph("data/image/PressAnyButton.png");

	// 画面サイズを取得
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");

	// 背景画像のロード
	_backgroundHandle = LoadGraph("data/image/back.jpg");

	// オープニングのテーマを再生する
	SoundManager::GetInstance().StartOp();
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_logoHandle);
	DeleteGraph(_backgroundHandle);
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
	// 王冠の更新処理
	_pCrown->Update();

	// いずれかのボタンでシーン移行
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// 決定音を鳴らす
		SoundManager::GetInstance().RingStartSE();

		// フェードアウトへ移行
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}

	// スタート指示を点滅させる
	if (_flame == 120) {
		_flame++;
	}
	else if (_flame == 1) {
		_flame--;
	}
	else if (_flame % 2 == 0) {
		_flame += 2;
	}
	else {
		_flame -= 2;
	}
}

void SceneTitle::NormalDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, _backgroundHandle, true);

	// ロゴの描画
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 5 * 2, 1.0f, 0.0f, _logoHandle, true, false);

	// 王冠画像の描画
	_pCrown->Draw();

	int alpha = (int)(255 * ((float)_flame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 8 * 7, 1.0f, 0.0f, _guideHandle, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
	NormalDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

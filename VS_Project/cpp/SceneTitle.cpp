#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"
#include "Application.h"

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

	// anybutton画像のロード
	_guideHandle = LoadGraph("data/image/PressAnyButton.png");
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");

	Scale = Vec3{ 0.12f,0.12f,0.12f };

	Position = Vec3{ 0.0f,25.0f,0.0f };

	_backgroundHandle = LoadGraph("data/image/back.jpg");

	SetCameraPositionAndTarget_UpVecY(VECTOR{ 0,0,0 }, VECTOR{ 0.0f,25.0f,0.0f });

	InitModel(MV1LoadModel("data/model/Player1.mv1"));

	_bgmHandle = LoadSoundMem("data/BGM/Title_BGM.mp3");

	PlaySoundMem(_bgmHandle, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_logoHandle);
	DeleteSoundMem(_bgmHandle);
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
	UpdateModel(GetTransformInstance());

	// いずれかのボタンでシーン移行
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {
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
	//DrawGraph(0, 0, _backgroundHandle, true);

	DrawModel();
	// ロゴの描画
	
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 5 * 2, 1.0f, 0.0f, _logoHandle, true, false);


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
		StopSoundMem(_bgmHandle);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>());
	}
}

void SceneTitle::FadeDraw() const
{
	// ロゴの描画
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 5 * 2, 1.0f, 0.0f, _logoHandle, true, false);


	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

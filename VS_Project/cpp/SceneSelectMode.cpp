#include "SceneSelectMode.h"
#include "SelectModeUi.h"
#include "DxLib.h"
#include "SkyDome.h"

SceneSelectMode::SceneSelectMode(bool slideInFlag)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelectMode::SlideInUpdate;
	_drawFunc = &SceneSelectMode::SlideInDraw;

	// UIインスタンス作成
	_pUi = std::make_shared<SelectModeUi>();

	// スカイドームインスタンス作成
	_pSkyDome = std::make_shared<SkyDome>();

	// スライド画像のロード
	_slideHandle = LoadGraph("data/image/Slide.png");

	// スライド画像の初期位置
	_slidePos = Vec2{ -300,0 };

	// カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);
}

SceneSelectMode::~SceneSelectMode()
{
}

void SceneSelectMode::Update()
{
	(this->*_updateFunc)();
}

void SceneSelectMode::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelectMode::NormalUpdate()
{
	_pSkyDome->Update();
	_pUi->Update();
}

void SceneSelectMode::NormalDraw() const
{
	_pSkyDome->Draw();

	_pUi->Draw();
}

void SceneSelectMode::SlideInUpdate()
{
	_pSkyDome->Update();
	// UIの更新処理
	_pUi->Update();

	// スライド画像の移動
	_slidePos.x -= 80;
}

void SceneSelectMode::SlideOutUpdate()
{
	_pSkyDome->Update();
	// UIの更新処理
	_pUi->Update();

	// スライド画像の移動 
	_slidePos.x += 80;
}

void SceneSelectMode::SlideInDraw() const
{
	_pSkyDome->Draw();
	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectMode::SlideOutDraw() const
{
	_pSkyDome->Draw();

	

	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

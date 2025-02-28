#include "SceneSelectMode.h"
#include "SelectModeUi.h"
#include "DxLib.h"
#include "SkyDome.h"
#include "Input.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SceneMenu.h"
#include "SceneSelect.h"
#include "SceneTutorial.h"

SceneSelectMode::SceneSelectMode(bool slideInFlag):
	_titleFrag(false),
	_returnSelectFrag(slideInFlag)
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

	// セレクトシーンから戻っていたらスライド画像は左から開く
	if (_returnSelectFrag) {
		_slidePos.x = -300;
	}
	else {
		_slidePos.x = -300;
	}

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
	// スカイドームの更新処理
	_pSkyDome->Update();

	// UIの更新処理
	_pUi->Update();

	// Bボタンでタイトルに戻る
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {

		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// タイトルに戻るフラグを立てる
		_titleFrag = true;

		// スライド画像の初期位置を設定する
		_slidePos.x = -3840;

		_updateFunc = &SceneSelectMode::SlideOutUpdate;
		_drawFunc = &SceneSelectMode::SlideOutDraw;
	}

	// Aボタンで選択しているボタンの処理をする
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		switch (_pUi->GetSelect())
		{
		case SOLO_MODE:
		case MULTI_MODE:
		case TUTORIAL_MODE:

			// スライド画像の初期位置を設定する
			_slidePos.x = 2000;

			// スライドアウト処理に移行する
			_updateFunc = &SceneSelectMode::SlideOutUpdate;
			_drawFunc = &SceneSelectMode::SlideOutDraw;
			break;
		case OPTION_MODE:
			// メニューシーンを追加する
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(INPUT_PAD_1));
			break;
		default:
			break;
		}
	}
}

void SceneSelectMode::NormalDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();
}

void SceneSelectMode::SlideInUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// UIの更新処理
	_pUi->Update();

	// スライド画像の移動

	if (_returnSelectFrag) {

		// スライド画像の移動
		_slidePos.x += 80;

		// 移動が終わったら処理の切り替え
		if (_slidePos.x >= 2000) {
			_updateFunc = &SceneSelectMode::NormalUpdate;
			_drawFunc = &SceneSelectMode::NormalDraw;
		}
	}
	else {

		// スライド画像の移動
		_slidePos.x -= 80;

		// 移動が終わったら処理の切り替え
		if (_slidePos.x <= -3840) {
			_updateFunc = &SceneSelectMode::NormalUpdate;
			_drawFunc = &SceneSelectMode::NormalDraw;
		}
	}

}

void SceneSelectMode::SlideOutUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();
	
	// UIの更新処理
	//_pUi->Update();

	// タイトルフラグで処理を変える
	if (_titleFrag) {
		// スライド画像の移動 
		_slidePos.x += 80;

		// 移動が終わったらシーン遷移
		if (_slidePos.x >= -300) {
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(true));
		}
	}
	else {
		// スライド画像の移動 
		_slidePos.x -= 80;

		// 移動が終わったらシーン遷移
		if (_slidePos.x <= -300) {
			switch (_pUi->GetSelect())
			{
			case SOLO_MODE:
				SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(0));
				break;
			case MULTI_MODE:

				break;
			case TUTORIAL_MODE:
				SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTutorial>());
				break;
			case OPTION_MODE:
			default:
				break;
			}
		}
	}
}

void SceneSelectMode::SlideInDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectMode::SlideOutDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

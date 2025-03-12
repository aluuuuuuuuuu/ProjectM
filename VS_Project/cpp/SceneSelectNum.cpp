#include "SceneSelectNum.h"
#include "SelectModeUi.h"
#include "SkyDome.h"
#include "SoundManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneSelectMode.h"
#include "PlayerManager.h"
#include "SceneSelect.h"
#include "SoundManager.h"

SceneSelectNum::SceneSelectNum()
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelectNum::SlideInUpdate;
	_drawFunc = &SceneSelectNum::SlideInDraw;

	// Uiインスタンス作成
	_pUi = std::make_shared<SelectModeUi>(false);

	// スカイドームインスタンス作成
	_pSkyDome = std::make_shared<SkyDome>();

	// スライド画像のロード
	_slideHandle = LoadGraph("data/image/Slide.png");

	// セレクトシーンから戻っていたらスライド画像は左から開く
	if (_returnFrag) {
		_slidePos.x = -300;
	}
	else {
		_slidePos.x = -300;
	}

	// カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);

	// BGMの再生
	SoundManager::GetInstance().StartBGM(BGM_OPENING);
}

SceneSelectNum::~SceneSelectNum()
{
	DeleteGraph(_slideHandle);
}

void SceneSelectNum::Update()
{
	(this->*_updateFunc)();
}

void SceneSelectNum::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelectNum::NormalUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// UIの更新処理
	_pUi->Update();

	// Bボタンでモードセレクトに戻る
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {

		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// タイトルに戻るフラグを立てる
		_selectFrag = true;

		// スライド画像の初期位置を設定する
		_slidePos.x = -3840;

		_updateFunc = &SceneSelectNum::SlideOutUpdate;
		_drawFunc = &SceneSelectNum::SlideOutDraw;
	}

	// Aボタンで選択しているボタンの処理をする
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// 決定音を鳴らす
		SoundManager::GetInstance().RingSE(SE_CHARA_SELECT);

		// スライド画像の初期位置を設定する
		_slidePos.x = 2000;

		// スライドアウト処理に移行する
		_updateFunc = &SceneSelectNum::SlideOutUpdate;
		_drawFunc = &SceneSelectNum::SlideOutDraw;
	}


}

void SceneSelectNum::NormalDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();
}

void SceneSelectNum::SlideInUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// UIの更新処理
	_pUi->Update();

	// スライド画像の移動

	if (_selectFrag) {

		// スライド画像の移動
		_slidePos.x += 80;

		// 移動が終わったら処理の切り替え
		if (_slidePos.x >= 2000) {
			_updateFunc = &SceneSelectNum::NormalUpdate;
			_drawFunc = &SceneSelectNum::NormalDraw;
		}
	}
	else {

		// スライド画像の移動
		_slidePos.x -= 80;

		// 移動が終わったら処理の切り替え
		if (_slidePos.x <= -3840) {
			_updateFunc = &SceneSelectNum::NormalUpdate;
			_drawFunc = &SceneSelectNum::NormalDraw;
		}
	}

}

void SceneSelectNum::SlideOutUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// UIの更新処理
	//_pUi->Update();

	// タイトルフラグで処理を変える
	if (_selectFrag) {
		// スライド画像の移動 
		_slidePos.x += 80;

		// 移動が終わったらシーン遷移
		if (_slidePos.x >= -300) {

			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelectMode>(true));
			
		}
	}
	else {
		// スライド画像の移動 
		_slidePos.x -= 80;

		// 移動が終わったらシーン遷移
		if (_slidePos.x <= -300) {

			// プレイヤーデータ
			PlayerData data;

			data.aiFlag = false;
			data.playerNum = _pUi->GetSelect();

			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pUi->GetSelect()));
		}
	}
}

void SceneSelectNum::SlideInDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectNum::SlideOutDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// UIの描画処理
	_pUi->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

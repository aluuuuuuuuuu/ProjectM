#include "ScenePvp.h"
#include "StageManager.h"
#include "Player.h"
#include "StageCollisionManager.h"
#include "BulletManager.h"
#include "Input.h"
#include "MapBulletCollisionManager.h"
#include "Application.h"
#include "Vec3.h"
#include "SkyDome.h"
#include "SceneMenu.h"
#include "SceneManager.h"
#include "WedgewormManager.h"
#include "GameFlowManager.h"
#include "SceneResult.h"
#include "NumUtility.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "PlayerBulletCollisionManager.h"

ScenePvp::ScenePvp(PlayerData data):
	_frame(110)
{
	// タイトルのBGMを止める
	SoundManager::GetInstance().StopBGM(BGM_OPENING);

	// 各クラスのインスタンス作成
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// 禊虫マネージャー
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);				// バレットマネージャー
		_pStage = std::make_shared<StageManager>();													// ステージマネージャー
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// バレットコリジョンマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// ステージコリジョンマネージャー
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// プレイヤーマネージャー
		_pSkyDome = std::make_shared<SkyDome>();	// スカイドーム
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// ゲームフローマネージャー
		_pNum = std::make_shared<NumUtility>(0.5f, Vec2{ 734,100 });	// 数字ユーティリティ
		_pPlayerBulletCollisionManager = std::make_shared<PlayerBulletCollisionManager>(_pBulletManager, _pPlayerManager);
	}

	// ライトの設定
	{
		// ライティングを使用する
		SetUseLighting(true);

		// ライトのカラーを調整する
		SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

		// ライトの角度を設定
		SetLightDirection(VECTOR{ 1.0f, -1.0f ,0.0f, });
	}

	// 関数ポインタの初期化
	{
		_updateFunc = &ScenePvp::FadeInUpdate;
		_drawFunc = &ScenePvp::FadeInDraw;
	}

	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// スクリーンの作成
	MakeScreen();

}

ScenePvp::~ScenePvp()
{
	// ライトの削除
	DeleteLightHandleAll();

	// 描画範囲と描画先の中心の初期化
	SetDrawArea(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"));
	SetCameraScreenCenter(static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2), static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2));
}

void ScenePvp::Update()
{
	(this->*_updateFunc)();
}

void ScenePvp::Draw() const
{
	(this->*_drawFunc)();
}

void ScenePvp::NormalUpdate()
{
	// BGMを再生	
	SoundManager::GetInstance().StartBGM(BGM_BATTLE);

	// メニュー画面を開く
	for (int num = 0; num < _pPlayerManager->GetPlayerNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}

	// スカイドームの更新処理
	_pSkyDome->Update();

	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// ゲームフローの更新処理
	_pGameFlowManager->Update();

	// バレットの更新
	_pBulletManager->Update();

	// 禊虫の更新
	_pWedgewormManager->Update();

	// プレイヤーコリジョンマネージャーの更新
	_pPlayerBulletCollisionManager->Update();

	// ゲームが終了していたら終了時の処理に移る
	if (_pGameFlowManager->GetGameEnd()) {
		_updateFunc = &ScenePvp::EndUpdate;
		_drawFunc = &ScenePvp::EndDraw;
	}

	// 時間の更新処理
	_pNum->Update(_pGameFlowManager->GetGameTime());
}

void ScenePvp::NormalDraw() const
{
	// プレイヤーの画面の数だけ描画する
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// 描画先の設定
		SetDrawScreen(_screen[i]);

		// スクリーンのクリア
		ClearDrawScreen();

		// カメラの設定
		SetCameraNearFar(1.0f, 1000.0f);

		_pPlayerManager->CameraSet(i);

		//スカイドームの描画
		_pSkyDome->Draw();

		// バレットの描画
		_pBulletManager->Draw();

		// ステージの描画
		_pStage->DrawStage();

		// 禊虫の描画
		_pWedgewormManager->Draw();

		// エフェクトの描画
		EffectManager::GetInstance().Draw();

		// プレイヤーの描画
		_pPlayerManager->Draw(i);
	}

	// 描画先を戻す
	SetDrawScreen(DX_SCREEN_BACK);

	// スクリーンの描画
	if (_pPlayerManager->GetPlayerNum() == 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(960, 0, _screen[1], true);
	}
	else if (_pPlayerManager->GetPlayerNum() > 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(960, 0, _screen[1], true);
		DrawGraph(0, 540, _screen[2], true);
		DrawGraph(960, 540, _screen[3], true);
	}

	// 時間の更新処理
	_pNum->Draw();

}

void ScenePvp::EndUpdate()
{
	// ゲームフローマネージャーの更新
	_pGameFlowManager->Update();

	_pPlayerManager->Update();

	_frame++;
	if (_frame >= 110) {

		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	}

	//// ゲームが終了してから１２０フレームたてばリザルト画面へ移行
	//if (_pGameFlowManager->GetFlameCount() >= 180) {
	//	SoundManager::GetInstance().StopBGM(BGM_BATTLE);
	//	SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	//}
}

void ScenePvp::EndDraw() const
{

	NormalDraw();

	//// プレイヤーの画面の数だけ描画する
	//for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

	//	// カメラの設定
	//	_pPlayerManager->CameraSet(i);

	//	// 描画範囲の設定
	//	SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

	//	// 描画先の中心を設定
	//	SetCameraScreenCenter(static_cast<float>(_pPlayerManager->GetCenter(i).a), static_cast<float>(_pPlayerManager->GetCenter(i).b));

	//	//スカイドームの描画
	//	_pSkyDome->Draw();

	//	// バレットの描画
	//	_pBulletManager->Draw();

	//	// ステージの描画
	//	_pStage->DrawStage();

	//	// 禊虫の描画
	//	_pWedgewormManager->Draw();
	//	// プレイヤーの描画
	//	_pPlayerManager->Draw(i);
	//}
}

void ScenePvp::FadeInUpdate()
{
	// 通常の更新
	NormalUpdate();

	_frame--;
	if (_frame == 0) {
		_updateFunc = &ScenePvp::NormalUpdate;
		_drawFunc = &ScenePvp::NormalDraw;
	}
}

void ScenePvp::FadeInDraw() const
{
	// 通常の描画
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 110));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScenePvp::MakeScreen()
{
	if (_pPlayerManager->GetPlayerNum() == 2) {
		_screen.push_back(DxLib::MakeScreen(960, 1080, true));
		_screen.push_back(DxLib::MakeScreen(960, 1080, true));
	}
	else {
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
	}
}

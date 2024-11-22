#include "SceneGrapple.h"
#include "SceneTest.h"
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

SceneGrapple::SceneGrapple()
{
	// 初期シーンを設定
	PlayerData data;

	data.playerNum = 1;
	data.charactor[0] = 1;

	// インスタンス
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// 禊虫マネージャー
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);				// バレットマネージャー
		_pStage = std::make_shared<StageManager>();													// ステージマネージャー
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// バレットコリジョンマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// ステージコリジョンマネージャー
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// プレイヤーマネージャー
		_pSkyDome = std::make_shared<SkyDome>();	// スカイドーム
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// ゲームフローマネージャー
	}
}

SceneGrapple::~SceneGrapple()
{
}

void SceneGrapple::Update()
{
	for (int num = 0; num < _pPlayerManager->GetPlayerNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}


	// スカイドームの更新処理
	_pSkyDome->Update();

	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// バレットの更新
	_pBulletManager->Update();

	// 禊虫の更新
	_pWedgewormManager->Update();

}

void SceneGrapple::Draw() const
{
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// カメラの設定
		_pPlayerManager->CameraSet(i);

		// 描画範囲の設定
		SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

		// 描画先の中心を設定
		SetCameraScreenCenter(static_cast<float>(_pPlayerManager->GetCenter(i).a), static_cast<float>(_pPlayerManager->GetCenter(i).b));

		//スカイドームの描画
		_pSkyDome->Draw();

		// バレットの描画
		_pBulletManager->Draw();

		// ステージの描画
		_pStage->DrawStage();

		// 禊虫の描画
		_pWedgewormManager->Draw();

		// プレイヤーの描画
		_pPlayerManager->Draw(i);
	}
}

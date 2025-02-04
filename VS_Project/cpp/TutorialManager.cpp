#include "TutorialManager.h"
#include "BulletManager.h"
#include "StageManager.h"
#include "MapBulletCollisionManager.h"
#include "StageCollisionManager.h"
#include "PlayerManager.h"
#include "SkyDome.h"
#include "WedgewormManager.h"
#include "EffectManager.h"

TutorialManager::TutorialManager():
	_frame(60)
{
	PlayerData data;

	data.aiFlag = false;
	data.character[PLAYER_ONE] = 0;
	data.playerNum = PLAYER_ONE;

	// 各クラスのインスタンス作成
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// 禊虫マネージャ
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);	// バレットマネージャー
		_pStage = std::make_shared<StageManager>();													// ステージマネージャー
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// バレットコリジョンマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// ステージコリジョンマネージャー
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// プレイヤーマネージャー
		_pSkyDome = std::make_shared<SkyDome>();	// スカイドーム
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
	_updateFunc = &TutorialManager::CameraUpdate;
	_drawFunc = &TutorialManager::ShareDraw;

	// プレイヤーの更新処理
	_pPlayerManager->Update();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Update()
{
	(this->*_updateFunc)();
}

void TutorialManager::Draw() const
{
	(this->*_drawFunc)();
}

void TutorialManager::CameraUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// バレットの更新
	_pBulletManager->Update();

	// 禊虫の更新
	_pWedgewormManager->Update();
}

void TutorialManager::MoveUpdate()
{
}

void TutorialManager::JumpUpdate()
{
}

void TutorialManager::ShotUpdate()
{
}

void TutorialManager::SelectUpdate()
{
}

void TutorialManager::LastUpdate()
{
}

void TutorialManager::ShareDraw() const
{
	// カメラの設定
	_pPlayerManager->CameraSet(0);

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
	_pPlayerManager->Draw(0);
}

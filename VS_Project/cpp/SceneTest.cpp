#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
#include "PlayerManager.h"
#include "StageCollisionManager.h"
#include "BulletManager.h"
#include "Input.h"
#include "MapBulletCollisionManager.h"
#include "Application.h"

SceneTest::SceneTest(int playerNum)
{
	// 各クラスのインスタンス作成
	{
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager);				// バレットマネージャー
		_pStage = std::make_shared<StageManager>();													// ステージマネージャー
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// バレットコリジョンマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// ステージコリジョンマネージャー
		_pPlayerManager = std::make_shared<PlayerManager>(_pStageCollisionManager, _pBulletManager, playerNum);	// プレイヤーマネージャー
	}

	// 関数ポインタの初期化
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*_updateFunc)();
}

void SceneTest::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTest::NormalUpdate()
{
	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// バレットの更新
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// 描画範囲の設定
		SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

		// 描画先の中心を設定
		SetCameraScreenCenter(_pPlayerManager->GetCenter(i).a, _pPlayerManager->GetCenter(i).b);

		// バレットの描画
		_pBulletManager->Draw();

		// ステージの描画
		_pStage->DrawStage();

		// プレイヤーの描画
		_pPlayerManager->Draw(i);
	}
}

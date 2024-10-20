#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
#include "StageCollisionManager.h"
#include "BulletManager.h"

SceneTest::SceneTest()
{
	// 各クラスのインスタンス作成
	{
		_pBulletManager = std::make_shared <BulletManager>();	// バレットマネージャー
		_pStage = std::make_shared<StageManager>();	// ステージマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);	// ステージコリジョンマネージャー
		_pPlayer = std::make_shared<Player>(_pStageCollisionManager,_pBulletManager);		// プレイヤー
	}

	// 関数ポインタの初期化
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}

	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/PlayerCamera.csv");
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

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}

void SceneTest::NormalUpdate()
{
	// プレイヤーの更新処理
	_pPlayer->Update();

	// バレットの更新
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	// グリッドの描画
	//DrawGrid();

	// バレットの描画
	_pBulletManager->Draw();
	
	// ステージブロックの描画
	_pStage->DrawStage();

	// プレイヤーの描画
	_pPlayer->Draw();
}

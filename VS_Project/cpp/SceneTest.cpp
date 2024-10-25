#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
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

		for (int a = 0; a < playerNum; a++) {
			_pPlayer.push_back(std::make_shared<Player>(_pStageCollisionManager, _pBulletCollsionManager, a));
		}
	}

	// 関数ポインタの初期化
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}

	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
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
	for (auto& pl : _pPlayer) {
		pl->Update();
	}

	// バレットの更新
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	for (auto& pl : _pPlayer) {

		// カメラのセット
		pl->CameraSet();

		// 描画範囲の設定
		VECTOR4 area = CreateDrawArea(_pPlayer.size());
		Vec2 center = CreateScreenCenter(_pPlayer.size());

		// 描画範囲の設定
		SetDrawArea(area.a, area.b, area.c, area.d);

		// 描画先の中心を設定
		SetCameraScreenCenter(center.intX(), center.intY());

		// バレットの描画
		_pBulletManager->Draw();

		// ステージの描画
		_pStage->DrawStage();

		// プレイヤーの描画
		for (auto& pll : _pPlayer) {
			pll->Draw();
		}
	}





	// 左上画面
	{
		// プレイヤー1のカメラのセット
		_pPlayer->CameraSet();

		// 左半分のみ描画
		SetDrawArea(0, 0, 800, 900);
		SetCameraScreenCenter(400, 450);

		// バレットの描画
		_pBulletManager->Draw();

		// ステージブロックの描画
		_pStage->DrawStage();

		// プレイヤーの描画
		_pPlayer->Draw();
		_pPlayer1->Draw();
		//_pPlayer2->Draw();
		//_pPlayer3->Draw();
	}

	// 右上画面
	{
		// プレイヤー2のカメラのセット
		_pPlayer1->CameraSet();

		// 右半分のみ描画
		SetDrawArea(800, 0, 1600, 900);
		SetCameraScreenCenter(1200, 450);

		// バレットの描画
		_pBulletManager->Draw();

		// ステージブロックの描画
		_pStage->DrawStage();

		// プレイヤーの描画
		_pPlayer1->Draw();
		//_pPlayer2->Draw();
		//_pPlayer3->Draw();
		_pPlayer->Draw();
	}





	//// 左上画面
	//{
	//	// プレイヤー1のカメラのセット
	//	_pPlayer->CameraSet();

	//	// 左半分のみ描画
	//	SetDrawArea(0, 0, 960, 540);
	//	SetCameraScreenCenter(480, 270);

	//	// バレットの描画
	//	_pBulletManager->Draw();

	//	// ステージブロックの描画
	//	_pStage->DrawStage();

	//	// プレイヤーの描画
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//}

	//// 右上画面
	//{
	//	// プレイヤー2のカメラのセット
	//	_pPlayer1->CameraSet();

	//	// 右半分のみ描画
	//	SetDrawArea(960, 0, 19920, 540);
	//	SetCameraScreenCenter(1440, 270);

	//	// バレットの描画
	//	_pBulletManager->Draw();

	//	// ステージブロックの描画
	//	_pStage->DrawStage();

	//	// プレイヤーの描画
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}

	//// 左下画面
	//{
	//	// プレイヤー3のカメラのセット
	//	_pPlayer2->CameraSet();

	//	// 右半分のみ描画
	//	SetDrawArea(0, 540, 960, 1080);
	//	SetCameraScreenCenter(480, 810);

	//	// バレットの描画
	//	_pBulletManager->Draw();

	//	// ステージブロックの描画
	//	_pStage->DrawStage();

	//	// プレイヤーの描画
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}

	//// 右下画面
	//{
	//	// プレイヤー4のカメラのセット
	//	_pPlayer3->CameraSet();

	//	// 右半分のみ描画
	//	SetDrawArea(960, 540, 1920, 1080);
	//	SetCameraScreenCenter(1440, 810);

	//	// バレットの描画
	//	_pBulletManager->Draw();

	//	// ステージブロックの描画
	//	_pStage->DrawStage();

	//	// プレイヤーの描画
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
}

VECTOR4 SceneTest::CreateDrawArea(int num) const
{
	return VECTOR4();
}

Vec2 SceneTest::CreateScreenCenter(int num) const
{
	return Vec2();
}

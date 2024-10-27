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
			_pPlayer.push_back(std::make_shared<Player>(_pStageCollisionManager, _pBulletManager, a));
		}
	}

	// ウィンドウの高さと幅を取得しておく
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");

	// 描画範囲とカメラセンターの作成
	int num = 0;
	for (auto& pl : _pPlayer) {
		_drawArea[num] = CreateDrawArea(num, _windowWidth, _windowHeight);		// 描画範囲
		_cameraSenter[num] = CreateScreenCenter(num, _windowWidth, _windowHeight);	// カメラのセンター
		num++;
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
	for (auto& pl : _pPlayer) {
		pl->Update();
	}

	// バレットの更新
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	int num = 0;
	for (auto& pl : _pPlayer) {

		// カメラのセット
		pl->CameraSet();

		// 描画範囲の設定
		SetDrawArea(_drawArea[num].a, _drawArea[num].b, _drawArea[num].c, _drawArea[num].d);

		// 描画先の中心を設定
		SetCameraScreenCenter(static_cast<float>(_cameraSenter[num].a), static_cast<float>(_cameraSenter[num].b));

		// バレットの描画
		_pBulletManager->Draw();

		// ステージの描画
		_pStage->DrawStage();

		// プレイヤーの描画
		for (auto& pll : _pPlayer) {
			pll->Draw();
		}
	}

	//// 左上画面
	//{
	//	// プレイヤー1のカメラのセット
	//	_pPlayer->CameraSet();
	//
	//	// 左半分のみ描画
	//	SetDrawArea(0, 0, 800, 900);
	//	SetCameraScreenCenter(400, 450);
	//
	//	// バレットの描画
	//	_pBulletManager->Draw();
	//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
	//
	//	// プレイヤーの描画
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	//_pPlayer2->Draw();
	//	//_pPlayer3->Draw();
	//}
	//
	//// 右上画面
	//{
	//	// プレイヤー2のカメラのセット
	//	_pPlayer1->CameraSet();
	//
	//	// 右半分のみ描画
	//	SetDrawArea(800, 0, 1600, 900);
	//	SetCameraScreenCenter(1200, 450);
	//
	//	// バレットの描画
	//	_pBulletManager->Draw();
	//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
	//
	//	// プレイヤーの描画
	//	_pPlayer1->Draw();
	//	//_pPlayer2->Draw();
	//	//_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
	//
	//
	//
	//
	//
	//// 左上画面
	//{
	//	// プレイヤー1のカメラのセット
	//	_pPlayer->CameraSet();
	//
	//	// 左半分のみ描画
	//	SetDrawArea(0, 0, 960, 540);
	//	SetCameraScreenCenter(480, 270);
	//
	//	// バレットの描画
	//	_pBulletManager->Draw();
	//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
	//
	//	// プレイヤーの描画
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//}
	//
	//// 右上画面
	//{
	//	// プレイヤー2のカメラのセット
	//	_pPlayer1->CameraSet();
	//
	//	// 右半分のみ描画
	//	SetDrawArea(960, 0, 19920, 540);
	//	SetCameraScreenCenter(1440, 270);
	//
	//	// バレットの描画
	//	_pBulletManager->Draw();
	//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
	//
	//	// プレイヤーの描画
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
	//
	//// 左下画面
	//{
	//	// プレイヤー3のカメラのセット
	//	_pPlayer2->CameraSet();
//
	//	// 右半分のみ描画
	//	SetDrawArea(0, 540, 960, 1080);
	//	SetCameraScreenCenter(480, 810);
//
	//	// バレットの描画
	//	_pBulletManager->Draw();
//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
//
	//	// プレイヤーの描画
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
//
	//// 右下画面
	//{
	//	// プレイヤー4のカメラのセット
	//	/_pPlayer3->CameraSet();
//
	//	// 右半分のみ描画
	//	SetDrawArea(960, 540, 1920, 1080);
	//	/SetCameraScreenCenter(1440, 810);
//
	//	// バレットの描画
	//	_pBulletManager->Draw();
//
	//	// ステージブロックの描画
	//	_pStage->DrawStage();
//
	//	// プレイヤーの描画
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
}

VECTOR4 SceneTest::CreateDrawArea(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int halfWidth = scWidth / 2;
	int halfHeight = scHeight / 2;

	// プレイヤーの総数で処理を切り替える
	switch (size)
	{
	case 1:
		return VECTOR4{ 0,0,scWidth,scHeight };
		break;
	case 2:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth , scHeight };
		}
		else {
			return VECTOR4{ halfWidth, 0,scWidth ,
							scHeight };
		}
		break;

	case 3:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		break;

	case 4:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else if (num == 2) {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		else {
			return VECTOR4{ halfWidth ,halfHeight ,
							scWidth,scHeight };
		}
		break;
	default:
		return VECTOR4{};
		break;
	}
}

VECTOR2 SceneTest::CreateScreenCenter(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int width;
	int height;

	switch (size)
	{
	case 1:
		return VECTOR2{ scWidth / 2,scHeight / 2 };
		break;

	case 2:

		width = scWidth / 2;
		height = scHeight / 2;

		if (num == 0) {
			return VECTOR2{ width, height };
		}
		else {
			return VECTOR2{ width * 3, height };
		}
		break;

	case 3:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else {
			return VECTOR2{ width, height * 3 };
		}
		break;

	case 4:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else if (num == 2) {
			return VECTOR2{ width, height * 3 };
		}
		else {
			return VECTOR2{ width * 3, height * 3 };
		}
		break;
	default:
		break;
	}
}

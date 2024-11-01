#include "Application.h"
#include "DxLib.h"
#include "Constant.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

bool Application::Init()
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/Application.csv");

	// ウィンドウモードの設定
	ChangeWindowMode(true);

	// ウィンドウ名の設定
	DxLib::SetWindowTextDX("ProjectM");

	// 画面サイズの設定
	SetWindowSize(GetConstantInt("SCREEN_WIDTH"),
		GetConstantInt("SCREEN_HEIGHT"));

	// 解像度の設定
	SetGraphMode(GetConstantInt("RESOLUTION_WIDTH"),
		GetConstantInt("RESOLUTION_HEIGHT"),
		GetConstantInt("COLOR_BIT"));

	// 背面の描画を行わない
	SetUseBackCulling(true);

	// ライティングを使用する
	SetUseLighting(true);

	// ライトのカラーを調整する
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	// ライトの角度を設定
	SetLightDirection(VECTOR{ 1.0f, -1.0f ,0.0f, });

	// ニアレストネイバー法で描画する
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Dxlibの初期化
	if (DxLib_Init() == -1) return false;

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// バックバッファに描画する
	SetDrawScreen(DX_SCREEN_BACK);

	// 背景色の設定
	SetBackgroundColor(100, 100, 255);

	// カーソルの表示設定
	SetMouseDispFlag(true);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	

	return true;
}

void Application::Run()
{
	// シーンマネージャーのインスタンスを取得
	auto& manager = SceneManager::GetInstance();
	int a = 0;
	// 初期シーンを設定
	manager.ChangeScene(std::make_shared <SceneSelect>());

	// インプットのインスタンスを取得
	auto& input = Input::GetInstance();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// Zバッファを使用して書き込む
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		/*ゲーム処理*/

		// 更新処理
		input.Update();
		manager.SceneUpdate();

		manager.SceneDraw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// managerのフラグでゲームを終了させる
		if (manager.GetGameEnd()) break;

		// escで終了（仮）
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	// 終了処理を行う
	Terminate();
}

void Application::Terminate()
{
	DxLib_End();    // DXライブラリの終了処理
}

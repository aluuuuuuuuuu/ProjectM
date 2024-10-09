#pragma once
#include "Singleton.h"
#include "Constant.h"

// アプリケーション全体の管理を行うシングルトンクラス
class Application :
	public Singleton<Application>,
	public Constant
{
	friend class Singleton<Application>;

public:
	// 初期処理
	bool Init();

	// メイン処理
	void Run();

private:
	// プライベートコンストラクタ
	Application() {};

	// 終了処理はパブリックでは呼べない
	void Terminate();
};

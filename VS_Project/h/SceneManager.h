#pragma once
#include <memory>
#include <list>
#include "Singleton.h"

class Input;
class SceneBase;
// シーンの管理を行うシングルトンクラス
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	
	// 実行中の要素を切り替える
	void ChangeScene(std::shared_ptr<SceneBase> next);

	// 実行中の要素を更新処理
	void SceneUpdate();

	// すべての要素を描画処理
	void SceneDraw() const;

	// ゲームを終了させるフラグを管理する
	void GameEnd();
	bool GetGameEnd();

private:
	// プライベートコンストラクタ
	SceneManager() {};

	// 各シーンのシェアポインタを格納するリスト配列
	std::list<std::shared_ptr<SceneBase>> _pScene;

	// ゲーム終了フラグ
	bool m_endFlag = false;
};


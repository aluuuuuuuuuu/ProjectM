#include "SceneManager.h"
#include "SceneBase.h"
#include "Application.h"

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> next)
{
	// リストが空だったら末尾に追加
	if (_pScene.empty()) {
		_pScene.push_back(next);
	}
	else {
		_pScene.back() = next;	// 末尾のものを入れ替える
	}
}

void SceneManager::SceneUpdate()
{
	// 末尾のみ更新
	_pScene.back()->Update();
}

void SceneManager::SceneDraw() const
{
	// 末尾のみ描画
	_pScene.back()->Draw();
}

// ゲーム終了フラグをtrueにする
void SceneManager::GameEnd()
{
	m_endFlag = true;
}

// ゲーム終了フラグを返す
bool SceneManager::GetGameEnd()
{
	return m_endFlag;
}

#include "SceneManager.h"
#include "SceneBase.h"
#include "Application.h"

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> next)
{
	// リストが空だったら末尾に追加
	if (m_pScene.empty()) {
		m_pScene.push_back(next);
	}
	else {
		m_pScene.back() = next;	// 末尾のものを入れ替える
	}
}

void SceneManager::SceneUpdate()
{
	// 末尾のみ更新
	m_pScene.back()->Update();
}

void SceneManager::SceneDraw() const
{
	// 末尾のみ描画
	m_pScene.back()->Draw();
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

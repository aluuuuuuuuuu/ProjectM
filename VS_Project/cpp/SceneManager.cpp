#include "SceneManager.h"
#include "SceneBase.h"
#include "Application.h"

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> next)
{
	// ���X�g���󂾂����疖���ɒǉ�
	if (m_pScene.empty()) {
		m_pScene.push_back(next);
	}
	else {
		m_pScene.back() = next;	// �����̂��̂����ւ���
	}
}

void SceneManager::SceneUpdate()
{
	// �����̂ݍX�V
	m_pScene.back()->Update();
}

void SceneManager::SceneDraw() const
{
	// �����̂ݕ`��
	m_pScene.back()->Draw();
}

// �Q�[���I���t���O��true�ɂ���
void SceneManager::GameEnd()
{
	m_endFlag = true;
}

// �Q�[���I���t���O��Ԃ�
bool SceneManager::GetGameEnd()
{
	return m_endFlag;
}

#include "SceneManager.h"
#include "SceneBase.h"
#include "Application.h"

void SceneManager::ChangeScene(std::shared_ptr<SceneBase> next)
{
	// ���X�g���󂾂����疖���ɒǉ�
	if (_pScene.empty()) {
		_pScene.push_back(next);
	}
	else {
		_pScene.back() = next;	// �����̂��̂����ւ���
	}
}

void SceneManager::SceneUpdate()
{
	// �����̂ݍX�V
	_pScene.back()->Update();
}

void SceneManager::SceneDraw() const
{
	// �����̂ݕ`��
	_pScene.back()->Draw();
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

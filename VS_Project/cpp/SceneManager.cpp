#include "SceneManager.h"
#include "SceneBase.h"
#include "Application.h"
#include "Input.h"
#include "SceneMenu.h"

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
	for (auto& scene : _pScene) {
		scene->Draw();
	}
}

void SceneManager::PushScene(std::shared_ptr<SceneBase> surface)
{
	_pScene.push_back(surface);
}

void SceneManager::PopScene()
{
	// �V�[���z��2�ȏ�̗v�f�������Ă���Έ�ԏ�̗v�f����菜��
	if (_pScene.size() > 1) {
		_pScene.pop_back();
	}
}

void SceneManager::GameEnd()
{
	_endFlag = true;
}

bool SceneManager::GetGameEnd()
{
	return _endFlag;
}

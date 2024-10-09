#pragma once
#include <memory>
#include <list>
#include "Singleton.h"

class Input;
class SceneBase;
// �V�[���̊Ǘ����s���V���O���g���N���X
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	
	// ���s���̗v�f��؂�ւ���
	void ChangeScene(std::shared_ptr<SceneBase> next);

	// ���s���̗v�f���X�V����
	void SceneUpdate();

	// ���ׂĂ̗v�f��`�揈��
	void SceneDraw() const;

	// �Q�[�����I��������t���O���Ǘ�����
	void GameEnd();
	bool GetGameEnd();

private:
	// �v���C�x�[�g�R���X�g���N�^
	SceneManager() {};

	// �e�V�[���̃V�F�A�|�C���^���i�[���郊�X�g�z��
	std::list<std::shared_ptr<SceneBase>> m_pScene;

	// �Q�[���I���t���O
	bool m_endFlag = false;
};


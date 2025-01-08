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
	
	/// <summary>
	/// ���s���̗v�f��؂�ւ���
	/// </summary>
	/// <param name="next">�؂�ւ���V�[���̃|�C���^</param>
	void ChangeScene(std::shared_ptr<SceneBase> next);

	/// <summary>
	/// ���s���̗v�f�̍X�V
	/// </summary>
	void SceneUpdate();

	/// <summary>
	/// ���ׂĂ̗v�f��`��
	/// </summary>
	void SceneDraw() const;

	/// <summary>
	/// ���s���̃V�[���̏�ɒǉ��̃V�[����ǉ�����
	/// </summary>
	/// <param name="surface">�ǉ�����V�[���̃|�C���^</param>
	void PushScene(std::shared_ptr<SceneBase> surface);

	/// <summary>
	/// �ǉ��̃V�[������������
	/// </summary>
	void PopScene();

	/// <summary>
	/// �Q�[���I���t���O�𗧂Ă�
	/// </summary>
	void GameEnd();

	/// <summary>
	/// �Q�[���I���t���O���擾����
	/// </summary>
	/// <returns></returns>
	bool GetGameEnd();


private:
	// �v���C�x�[�g�R���X�g���N�^
	SceneManager() {};

	// �e�V�[���̃V�F�A�|�C���^���i�[���郊�X�g�z��
	std::list<std::shared_ptr<SceneBase>> _pScene;

	// �Q�[���I���t���O
	bool _endFlag = false;

};


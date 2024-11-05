#pragma once
#include <Crown.h>
#include "Vec2.h"

class SceneTitle;
class Crown
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Crown(SceneTitle& scene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Crown();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
private:

	// �����摜�n���h��
	int _crownHandle;

	// �����p�[�e�B�N���摜�n���h��
	int _crownParticleHandle1;
	int _crownParticleHandle2;
	int _crownParticleHandle3;

	// ���̕ϐ��̒��Ƀp�[�e�B�N���摜�n���h�������X�ɓ����Ă���
	int _crownParticle;

	// �t���[���J�E���g
	int _flame1;
	int _flame2;

	bool _flame1Flag;

	bool _blinkingFlag;
	
	Vec2 _dispPos;
};


#pragma once
#include "Constant.h"
#include "Vec3.h"
#include "Components.h"

class PlayerCamera :
	public Constant,
	public Transform
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <param name="padNum">�p�b�h�i���o�[</param>
	/// <param name="forward">�v���C���[�̕����x�N�g��</param>
	PlayerCamera(Vec3 pos, int padNum, Vec3 forward);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerCamera();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <param name="forward">�v���C���[�̕����x�N�g��</param>
	void Update(Vec3 pos, Vec3 forward, Vec3 angle);

	/// <summary>
	/// �^�[�Q�b�g�̍��W���擾����
	/// </summary>
	/// <returns>�^�[�Q�b�g�̍��W</returns>
	Vec3 GetTarget();


private:

	/// <summary>
	/// ��]
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <returns>��]��̍��W</returns>
	/// <param name="forward">�v���C���[�̕����x�N�g��</param>
	Vec3 Rotate(Vec3 pos, Vec3 forward);


	/// <summary>
	/// �����̍��W����]������
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <returns>��]��̍��W</returns> 
	Vec3 RotatePos(Vec3 pos);

	Vec3 _target;

	// �J�������甭�����郉�C�g�n���h��
	int _lightHandle;

	int _padNum;
};


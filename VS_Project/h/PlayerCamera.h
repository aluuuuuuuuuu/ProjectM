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
	PlayerCamera(Vec3 pos);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	void Update(Vec3 pos);


private:

	/// <summary>
	/// ��]
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <returns>��]��̍��W</returns>
	Vec3 Rotate(Vec3 pos);


	/// <summary>
	/// �����̍��W����]������
	/// </summary>
	/// <param name="pos">�v���C���[�̍��W</param>
	/// <returns>��]��̍��W</returns> 
	Vec3 RotatePos(Vec3 pos);

	// �J�������甭�����郉�C�g�n���h��
	int _lightHandle;
};


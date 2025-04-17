#pragma once
#include "Vec3.h"
#include <memory>
#include "Components.h"
#include "Constant.h"

class ItemBase :
	public Transform,
	public Model,
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ItemBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ItemBase();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// �A�C�e���^�C�v�̎擾
	/// </summary>
	/// <returns>�A�C�e���^�C�v�萔</returns>
	int GetType() const;

	/// <summary>
	/// ���g�̍폜���n�߂�
	/// </summary>
	void KillItem();
	
	/// <summary>
	/// ���g�̎��S�t���O��Ԃ�
	/// </summary>
	/// <returns>true:����ł���</returns>
	bool IsDead() const;

	/// <summary>
	/// ���g�̖����t���O��Ԃ�
	/// </summary>
	/// <returns>true:����</returns>
	bool IsInvalid() const;

protected:

	// ���S�t���O
	bool _deadFlag = false;

	// ���g�̃A�C�e���̎��
	int _itemType = -1;

	// �����t���O
	bool _invalidFlag = false;

	// �v���C���[�Ɠ��������t���O
	bool _playerCollisionFlag = false;

	// �ړ��x�N�g��
	Vec3 _moveVec;

	// ���~����~���Ă���̃t���[���J�E���^
	int _frame = 0;
};



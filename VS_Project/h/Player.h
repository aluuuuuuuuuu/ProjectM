#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"

class PlayerCamera;
class StageCollisionManager;
class Player:
	public Transform,
	public CapsuleCollision,
	public Model,
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player(std::shared_ptr<StageCollisionManager>& col);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

private:

	/// <summary>
	/// �R���g���[���[���͂ňړ��x�N�g�����쐬����
	/// </summary>
	/// <returns>�ړ��x�N�g��</returns>
	Vec3 CreateMoveVec();

	/// <summary>
	/// �W�����v�͂�Ԃ�
	/// </summary>
	/// <returns>�W�����v��</returns>
	float CreateYMoveScale();

	/// <summary>
	/// ���ݒn��ɂ��邩���肷��
	/// </summary>
	/// <returns>true:�n��ɂ���</returns>
	bool OnGround();

	/// <summary>
	/// �����̃x�N�g���������̉�]�l�ɍ��킹��Y����]������
	/// </summary>
	/// <param name="vec">�Ώۂ̃x�N�g��</param>
	/// <param name="angle">Y���̉�]�l</param>
	/// <returns>��]��̃x�N�g��</returns>
	Vec3 RotateVec(Vec3 vec, float angle);

	/// <summary>
	/// �����̃x�N�g���̌�����Y����]����
	/// </summary>
	/// <param name="moveVec">�ړ��x�N�g��</param>
	void RotateAngle(Vec3 moveVec);

	// Y���̈ړ���
	float _MoveScaleY;

	// �n��ɗ����Ă���t���O
	bool _isGround;

	// �O�t���[���̍��W
	Vec3 _frontPos;

	// �ړ��x�N�g��
	Vec3 _moveVec;

	//  �X�e�[�W�R���W�����}�l�[�W���[�̎Q��
	std::shared_ptr<StageCollisionManager>& _collManager;

	// �J�����|�C���^
	std::shared_ptr<PlayerCamera> _pCamera;
};


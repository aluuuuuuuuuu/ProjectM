#pragma once
#include "Components.h"
#include <memory>


class StageCollisionManager;
class Player:
	public Transform,
	public CapsuleCollision
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

	/// <summary>
	/// �V�[�����瓖���蔻�肵����̍��W��ݒ肷��
	/// </summary>
	void SetPos(Vec3 pos);
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

	// Y���̈ړ���
	float _yMoveScale;

	// �n��ɗ����Ă���t���O
	bool _isGround;

	// �O�t���[���̍��W
	Vec3 _frontPos;

	// �ړ��x�N�g��
	Vec3 _moveVec;

	//  �X�e�[�W�R���W�����}�l�[�W���[�̎Q��
	std::shared_ptr<StageCollisionManager>& _collManager;


};


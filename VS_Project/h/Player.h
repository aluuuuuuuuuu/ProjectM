#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"

class PlayerManager;
class BulletManager;
class PlayerCamera;
class StageCollisionManager;
class Player:
	public Transform,
	public CapsuleCollision,
	public Model,
	public Animation
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player(std::shared_ptr<StageCollisionManager>& col, std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum);

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
	/// �J�����̍��W���Z�b�g����
	/// </summary>
	void CameraSet() const;

private:



	/// <summary>
	/// ���g�̉�]
	/// </summary>
	void Rotate();

	/// <summary>
	/// �ړ��֐����܂Ƃ߂��֐�
	/// </summary>
	void Move();

	/// <summary>
	/// �J�����ɍ��킹�Ĉړ��x�N�g������]������
	/// </summary>
	
	/// <summary>
	/// �����̃��W�A���ɍ��킹�ăx�N�g������]������
	/// </summary>
	/// <param name="vec">��]������x�N�g��</param>
	/// <param name="angle">���W�A��</param>
	/// <returns>��]��̃x�N�g��</returns>
	Vec3 RotateMoveVec(Vec3 vec,float angle);

	/// <summary>
	/// �����蔻��n�֐����܂Ƃ߂��֐�
	/// </summary>
	void Collision();

	/// <summary>
	/// �R���g���[���[���͂ňړ��x�N�g�����쐬����
	/// </summary>
	/// <returns>�ړ��x�N�g��</returns>
	void CreateMoveVec();

	/// <summary>
	/// �W�����v�͂�Ԃ�
	/// </summary>
	/// <returns>�W�����v��</returns>
	void CreateYMoveScale();

	/// <summary>
	/// ���ݒn��ɂ��邩���肷��
	/// </summary>
	/// <returns>true:�n��ɂ���</returns>
	bool OnGround();

	/// <summary>
	/// Y���̉�]�l�������̒l�ɏ��X�ɋ߂Â��Ă���
	/// </summary>
	/// <param name="targetAngle">�ڕW�̒l</param>
	void RotateAngleY(float targetAngle);

	/// <summary>
	/// �J�����̌�����Y����]����
	/// </summary>
	void RotateAngleToCamera();

	/// <summary>
	/// �ړ��x�N�g���̌�����Y����]����
	/// </summary>
	void RotateAngleToVec();

	/// <summary>
	/// 2�����x�N�g�����p�x���Ƃ�8�ɕ��ނ���
	/// </summary>
	/// <returns>���ސ�</returns>
	int ClassifyDirection();

	void WalkRunAnimControl();

	// Y���̈ړ���
	float _moveScaleY;

	// �n��ɗ����Ă���t���O
	bool _isGround;

	// �O�t���[���̍��W
	Vec3 _frontPos;

	// �ړ��x�N�g��
	Vec3 _moveVec;

	// Y�������ɂȂ����J�E���g
	int _groundCount;

	//  �X�e�[�W�R���W�����}�l�[�W���[�̎Q��
	std::shared_ptr<StageCollisionManager>& _collManager;

	// �o���b�g�}�l�[�W���[�̎Q��
	std::shared_ptr<BulletManager>& _bulletManager;

	// �J�����|�C���^
	std::shared_ptr<PlayerCamera> _pCamera;

	// �����Ă���t���O
	bool _runFlag;

	// �g�p����p�b�h�̃i���o�[
	int _padNum;

	// �v���C���[�}�l�[�W���[�̎Q��
	PlayerManager& _manager;
};


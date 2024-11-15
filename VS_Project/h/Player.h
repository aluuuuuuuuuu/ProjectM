#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"

class PlayerManager;
class BulletManager;
class PlayerCamera;
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
	Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// �ړ��Ȃǂ̏���
	/// </summary>
	void Control();

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

	/// <summary>
	/// �n��t���O����肷��
	/// </summary>
	/// <returns>�O���E���h�t���O<returns>
	bool GetGroundFlag() const;

	/// <summary>
	/// �v���C���[�}�l�[�W���[����v���C���[���E��
	/// </summary>
	void KillPlayer();

private:

	/// <summary>
	/// Y���̉�]�l�������̒l�ɏ��X�ɋ߂Â��Ă���
	/// </summary>
	/// <param name="targetAngle">�ڕW�̒l</param>
	void RotateAngleY(float targetAngle);

	/// <summary>
	/// 2�����x�N�g�����p�x���Ƃ�8�ɕ��ނ���
	/// </summary>
	/// <returns>���ސ�</returns>
	int ClassifyDirection();

	/// <summary>
	/// �A�j���[�V��������֐�
	/// </summary>
	void AnimationContorol();

	/// <summary>
	/// �I�������e�𔭎˂���
	/// </summary>
	void BulletTrigger();

	// Y���̈ړ���
	float _moveScaleY;

	// �n��ɗ����Ă���t���O
	bool _groundFlag;

	// �O�t���[���̍��W
	Vec3 _frontPos;

	// �ړ��x�N�g��
	Vec3 _moveVec;

	// Y�������ɂȂ����J�E���g
	int _groundCount;

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

	// �c�i��
	int _bulletNum;

	// �����Ă�������̃x�N�g��
	Vec3 _forwardVec;

	// �O���b�v���[�ړ��p�P�ʃx�N�g��
	Vec3 _grapplerUnitVec;

	// �O���b�v���[�p�ړ���
	float _grapplerScale;

	// �I�����Ă���e�̗v�f�ԍ�
	int _selectBullet;

	// ���S�t���O
	bool _deadFlag;

};


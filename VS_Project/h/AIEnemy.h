#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"
#include "PlayerManager.h"

class BulletManager;
class BulletManager;
class AIEnemy :
	public Transform,
	public CapsuleCollision,
	public Model,
	public Animation
{
public:


    AIEnemy(std::shared_ptr<BulletManager>& bullet, BulletData& data);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~AIEnemy();

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
	/// �n��t���O����肷��
	/// </summary>
	/// <returns>�O���E���h�t���O<returns>
	bool GetGroundFlag() const;

	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetDeadFlag() const;

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

	// �g�p����p�b�h�̃i���o�[
	int _padNum;

	// �v���C���[�}�l�[�W���[�̎Q��
	PlayerManager& _manager;

	// �����Ă�������̃x�N�g��
	Vec3 _forwardVec;

	// �O���b�v���[�ړ��p�P�ʃx�N�g��
	Vec3 _grapplerUnitVec;

	// �O���b�v���[�p�ړ���
	float _grapplerScale;

	// ���S�t���O
	bool _deadFlag;

	// �o���b�g�f�[�^�̎Q��
	BulletData& _bulletData;
};


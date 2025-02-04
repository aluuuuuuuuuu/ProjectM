#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"
#include "PlayerManager.h"

class MyEffect;
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
	/// 
	/// </summary>
	/// <param name="bullet"></param>
	/// <param name="manager"></param>
	/// <param name="padNum"></param>
	/// <param name="data"></param>
	Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum,BulletData& data);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bullet"></param>
	/// <param name="manager"></param>
	/// <param name="data"></param>
	Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, BulletData& data);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Control();

	/// <summary>
	/// �`�揈��
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
	/// ���S�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetDeadFlag() const;

	/// <summary>
	/// �v���C���[�}�l�[�W���[����v���C���[���E��
	/// </summary>
	void KillPlayer();

	/// <summary>
	/// ���g�̃v���C���[�i���o�[��Ԃ�
	/// </summary>
	/// <returns>�v���C���[�i���o�[</returns>
	int GetPlayerNum() const;

private:

	// �R���g���[���֐��|�C���^
	using m_controlFunc_t = void (Player::*)();
	m_controlFunc_t _controlFunc = nullptr;

	// �R���g���[���֐��|�C���^
	using m_updateFunc_t = void (Player::*)();
	m_updateFunc_t _updateFunc = nullptr;

	/// <summary>
	/// �ړ��Ȃǂ̏���
	/// </summary>
	void ControlPl();

	/// <summary>
	/// ����AI
	/// </summary>
	void ControlAI();

	/// <summary>
	/// �X�V����
	/// </summary>
	void UpdatePl();

	/// <summary>
	/// AI�X�V����
	/// </summary>
	void UpdateAI();

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

	// AI�p�̃t���[���J�E���^
	int _frame;

	// AI�p��60�t���[���O�̍��W
	Vec3 _oldPos;

	std::shared_ptr<MyEffect> _pEffect;
};


#pragma once
#include <memory>
#include "Vec3.h"

class BulletManager;
class PlayerManager;
class PlayerBulletCollisionManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="bull">�o���b�g�}�l�[�W���[�̎Q��</param>
	/// <param name="pl">�v���C���[�}�l�[�W���[�̎Q��</param>
	PlayerBulletCollisionManager(std::shared_ptr<BulletManager>& bull,std::shared_ptr<PlayerManager>& pl);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerBulletCollisionManager();

	/// <summary>
	/// �}�C�t���[���e�ƃv���C���[�̓����蔻������
	/// </summary>
	void Update();

private:

	/// <summary>
	/// �ŋߐړ_�����߂�֐�
	/// </summary>
	/// <param name="A">�J�v�Z���̐�����A�|�C���g</param>
	/// <param name="B">�J�v�Z���̐�����B�|�C���g</param>
	/// <param name="P">���̒��S���W</param>
	/// <returns></returns>
	Vec3 closestPointOnSegment(Vec3& A, Vec3& B, Vec3& P);

	/// <summary>
	/// �J�v�Z���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="A">�J�v�Z���̐�����A�|�C���g</param>
	/// <param name="B">�J�v�Z���̐�����B�|�C���g</param>
	/// <param name="capsuleRadius">�J�v�Z���̔��a</param>
	/// <param name="sphereCenter">���̒��S���W</param>
	/// <param name="sphereRadius">���̔��a</param>
	/// <returns>�������Ă�����true</returns>
	bool capsuleSphereCollision(Vec3& A, Vec3& B, float capsuleRadius, Vec3& sphereCenter, float sphereRadius);

	// �o���b�g�}�l�[�W���[�̎Q��
	std::shared_ptr<BulletManager>& _pBulletManager;

	// �v���C���[�}�l�[�W���[�̎Q��
	std::shared_ptr<PlayerManager>& _pPlayerManager;


};


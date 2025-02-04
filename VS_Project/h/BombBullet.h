#pragma once
#include "BulletBase.h"
#include <memory>

class BulletManager;
class MapCollisionManager;
class BombBullet:
	public BulletBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dist">�����x�N�g��</param>
	/// <param name="pos">����������W</param>
	/// <param name="col">�R���W�����}�l�[�W���[</param>
	/// <param name="mgr">�o���b�g�}�l�[�W���[</param>
	/// <param name="plNum">�v���C���[�i���o�[</param>
	BombBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BombBullet();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

private:
	// �R���W�����}�l�[�W���[�̎Q��
	std::shared_ptr<MapBulletCollisionManager>& _collManager;

	// �o���b�g�}�l�[�W���[�̎Q��
	BulletManager& _bulletManager;

	// �����G�t�F�N�g
	std::shared_ptr<MyEffect> _explosionEffect;

	// �����G�t�F�N�g��`�悷�邽�߂̃t���[���J�E���^
	int _frame;
};


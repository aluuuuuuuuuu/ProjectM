#pragma once
#include <memory>
#include "BulletBase.h"

class MyEffect;
class BulletManager;
class MapBulletCollisionManager;
class NormalBullet :
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
	NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~NormalBullet();

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

	// �t���[���J�E���^
	int _frame;

	// �u���b�N�j��G�t�F�N�g
	std::shared_ptr<MyEffect> _destroyEffect;

};


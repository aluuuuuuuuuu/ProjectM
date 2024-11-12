#pragma once
#include "BulletBase.h"
#include <memory>
#include <list>
#include <Constant.h>

#define NORMAL_BULLET 0
#define GRAPPLER_BULLET 1

class MapBulletCollisionManager;
class BulletBase;
class BulletManager:
	public Constant
{
public:
	BulletManager(std::shared_ptr<MapBulletCollisionManager>& col);
	virtual ~BulletManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �v���C���[���ĂԊ֐��A�w��̒e�𔭎˂���
	/// </summary>
	/// <param name="bul">�e�̎��</param>
	/// <param name="dist">�����x�N�g��</param>
	/// <param name="pos">���W</param>
	void PushBullet(int bul, Vec3 dist, Vec3 pos);

	/// <summary>
	/// ����O���b�v���[�������������ǂ�����Ԃ��֐�
	/// </summary>
	/// <returns>�������Ă�����true</returns>
	bool IsCollisionBullet();

private:

	std::list<std::shared_ptr<BulletBase>> _pBullet;
	std::shared_ptr<MapBulletCollisionManager>& _collManager;
};

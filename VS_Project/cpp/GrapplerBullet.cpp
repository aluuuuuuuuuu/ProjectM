#include "GrapplerBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"

GrapplerBullet::GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr) :
	_distVec(dist),
	_gravity(0),
	_collManager(col),
	_bulletManager(mgr)

{
	// �����ʒu�̐ݒ�
	Position = pos;

	_bulletType = GRAPPLER_BULLET;
}

GrapplerBullet::~GrapplerBullet()
{
}

void GrapplerBullet::Update()
{
	if (!_colFlag) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED");
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	// �}�b�v�Ƃ̓����蔻����Ƃ�
	if (_collManager->CollisionBullet(Position, 3.0f,GRAPPLER_BULLET)) _collisionFlag = true;
}

void GrapplerBullet::Draw() const
{
	DrawSphere3D(Position.VGet(), 3.0f, 16, 0xff00ff, 0xff00ff, true);
}

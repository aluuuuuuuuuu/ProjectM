#include "BulletBase.h"

BulletBase::BulletBase():
	_deadFlag(false),
	_bulletType(-1)
{
}

bool BulletBase::IsDead() const
{
	return _deadFlag;
}

int BulletBase::GetBulletType() const
{
	return _bulletType;
}

bool BulletBase::GetCollisionFlag() const
{
	return _collisionFlag;
}

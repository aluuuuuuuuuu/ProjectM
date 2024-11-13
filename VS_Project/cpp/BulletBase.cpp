#include "BulletBase.h"

BulletBase::BulletBase():
	_deadFlag(false),
	_bulletType(-1),
	_collisionFlag(false),
	_invalidFlag(false),
	_playerNum(0),
	_gravity(0)
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

bool BulletBase::GetInvalidFlag() const
{
	return _invalidFlag;
}

void BulletBase::KillBullet()
{
	_invalidFlag = true;
}

int BulletBase::GetPlayerNum()
{
	return _playerNum;
}

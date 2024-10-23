#include "BulletBase.h"

BulletBase::BulletBase():
	_deadFlag(false)
{
}

bool BulletBase::IsDead() const
{
	return _deadFlag;
}
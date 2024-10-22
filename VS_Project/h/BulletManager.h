#pragma once
#include "BulletBase.h"
#include <memory>
#include <list>

#define NORMAL_BULLET 0

class MapBulletCollisionManager;
class BulletBase;
class BulletManager
{
public:
	BulletManager(std::shared_ptr<MapBulletCollisionManager>& col);
	virtual ~BulletManager();

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() const;

	void PushBullet(int bul, Vec3 dist, Vec3 pos);

	std::list<std::shared_ptr<BulletBase>> _pBullet;
private:

	std::shared_ptr<MapBulletCollisionManager>& _collManager;
};

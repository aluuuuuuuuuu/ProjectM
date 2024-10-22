#pragma once
#include <memory>
#include "BulletBase.h"

class MapBulletCollisionManager;
class NormalBullet:
	public BulletBase
{
public:
	NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col);
	virtual ~NormalBullet();

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() const;
private:

	Vec3 _distVec;

	float _gravity;

	std::shared_ptr<MapBulletCollisionManager>& _collManager;

};


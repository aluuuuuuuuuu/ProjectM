#pragma once
#include "BulletBase.h"

class NormalBullet:
	public BulletBase
{
public:
	NormalBullet(Vec3 dist, Vec3 pos);
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

};


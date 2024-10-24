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
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
private:

	Vec3 _distVec;

	float _gravity;

	std::shared_ptr<MapBulletCollisionManager>& _collManager;

};


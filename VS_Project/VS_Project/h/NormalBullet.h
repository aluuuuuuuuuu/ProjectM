#pragma once
#include <memory>
#include "BulletBase.h"

class BulletManager;
class MapBulletCollisionManager;
class NormalBullet:
	public BulletBase
{
public:
	NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr);
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

	Vec3 _distVec;

	float _gravity;

	std::shared_ptr<MapBulletCollisionManager>& _collManager;

	BulletManager& _bulletManager;
};


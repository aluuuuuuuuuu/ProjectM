#include "GrapplerBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "WedgewormManager.h"

GrapplerBullet::GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum, std::shared_ptr<WedgewormManager>& wedge) :
	_collManager(col),
	_bulletManager(mgr),
	_flame(0),
	_wedgeManager(wedge)

{
	// 初期位置の設定
	Position = pos;

	_bulletType = GRAPPLER_BULLET;

	_playerNum = plNum;

	_distVec = dist;
}

GrapplerBullet::~GrapplerBullet()
{
}

void GrapplerBullet::UpdatePl()
{
	if (!_collisionFlag) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED");
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	// マップとの当たり判定をとる
	if (_collManager->CollisionBullet(Position, 3.0f, GRAPPLER_BULLET)) _collisionFlag = true;

	// 禊虫との当たり判定をとる

	for (int i = 0; i < 2; i++) {
		Vec3 pos = _wedgeManager->GetPos(i);
		float dist = (pos - Position).Length();

		if (dist < 16.0f + 16.0f) {
			_collisionFlag = true;
		}
	}

	if (_invalidFlag) {
		_flame++;
		if (_flame >= 120) {
			_deadFlag = true;
		}
	}

}

void GrapplerBullet::Draw() const
{
	DrawSphere3D(Position.VGet(), 3.0f, 16, 0xff00ff, 0xff00ff, true);
}

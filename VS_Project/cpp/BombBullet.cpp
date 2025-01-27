#include "BombBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"

BombBullet::BombBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr)
{
	// 初期位置の設定
	Position = pos;

	_bulletType = BOMB_BULLET;

	_playerNum = plNum;

	_distVec = dist;
}

BombBullet::~BombBullet()
{
}

void BombBullet::Update()
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
	if (_collManager->CollisionBullet(Position, 3.0f, BOMB_BULLET)) _deadFlag = true;
}

void BombBullet::Draw() const
{
	DrawSphere3D(Position.VGet(), 3.0f, 16, 0xf0ff00, 0xf0ff00, true);
}

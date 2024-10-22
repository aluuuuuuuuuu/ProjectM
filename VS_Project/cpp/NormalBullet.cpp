#include "NormalBullet.h"
#include "MapBulletCollisionManager.h"

NormalBullet::NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col):
	_distVec(dist),
	_gravity(0),
	_collManager(col)
{
	// 定数の読み込み
	ReadCSV("data/constant/NormalBullet.csv");

	// 初期位置の設定
	Position = pos;
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Update()
{
	Position += _distVec * GetConstantFloat("SPEED");
	_gravity += GetConstantFloat("GRAVITY");
	Position.y -= _gravity;

	// マップとの当たり判定をとる
	_collManager->CollisionBullet(Position, 3.0f);
}

void NormalBullet::Draw() const
{
	DrawSphere3D(Position.VGet(), 3.0f, 16, 0x0000ff, 0x0000ff, true);
}

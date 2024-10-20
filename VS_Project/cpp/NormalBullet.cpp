#include "NormalBullet.h"

NormalBullet::NormalBullet(Vec3 dist, Vec3 pos):
	_distVec(dist)
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
}

void NormalBullet::Draw() const
{
	DrawSphere3D(Position.VGet(), 3.0f, 16, 0x0000ff, 0x0000ff, true);
}

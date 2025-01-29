#include "NormalBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"

NormalBullet::NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr)
{
	// 初期位置の設定
	Position = pos;

	// バレットタイプの設定
	_bulletType = NORMAL_BULLET;

	// 発射したプレイヤーの保存
	_playerNum = plNum;

	// 進む方向
	_distVec = dist;

	// エフェクトインスタンスの作成
	_pEffect = std::make_shared<MyEffect>(NORMAL_BULLET_EFFECT,pos);
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Update()
{
	// ポジションの更新
	Position += _distVec *  _bulletManager.GetConstantFloat("SPEED");

	// 重力の影響を与える
	_gravity += _bulletManager.GetConstantFloat("GRAVITY");
	Position.y -= _gravity;

	// 一定のラインを越えたら削除する
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	// マップとの当たり判定をとる
	if (_collManager->CollisionBullet(Position, 3.0f,NORMAL_BULLET)) _deadFlag = true;

	if (_deadFlag) {
		_pEffect->StopEffect();
	}

	_pEffect->Update(Position);
}

void NormalBullet::Draw() const
{
#ifdef _DEBUG
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0x0000ff, 0x0000ff, true);
#endif // DEBUG
}

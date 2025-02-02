#include "GrapplerBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "WedgewormManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundManager.h"

GrapplerBullet::GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum, std::shared_ptr<WedgewormManager>& wedge) :
	_collManager(col),
	_bulletManager(mgr),
	_flame(0),
	_wedgeManager(wedge)

{
	// 初期位置の設定
	Position = pos;

	// バレットタイプの設定
	_bulletType = GRAPPLER_BULLET;

	// 発射したプレイヤーの保存
	_playerNum = plNum;

	// 進む方向
	_distVec = dist;

	// エフェクトインスタンスの作成
	_pEffect = std::make_shared<MyEffect>(GRAPPLE_BULLET_EFFECT, pos);
}

GrapplerBullet::~GrapplerBullet()
{
	if (!_deadFlag) {
		_pEffect->StopEffect();
	}
}

void GrapplerBullet::Update()
{
	if (!_collisionFlag) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED");
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	// 一定のラインを越えたら削除する
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	// マップとの当たり判定をとる
	if (_collManager->CollisionBullet(Position, 3.0f, GRAPPLER_BULLET)) {

		_collisionFlag = true;
	}
	//// 禊虫との当たり判定をとる
	//for (int i = 0; i < 2; i++) {
	//	Vec3 pos = _wedgeManager->GetPos(i);
	//	float dist = (pos - Position).Length();

	//	if (dist < 16.0f + 16.0f) {
	//		_collisionFlag = true;
	//	}
	//}

	// 当たっても一定時間残るようにする
	if (_invalidFlag) {
		_flame++;
		if (_flame >= 80) {
			_deadFlag = true;
		}
	}
	
	// エフェクトの削除
	if (_deadFlag) {
		_pEffect->StopEffect();
	}

	// エフェクトの更新
	_pEffect->Update(Position);
}

void GrapplerBullet::Draw() const
{
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0xff00ff, 0xff00ff, true);
}

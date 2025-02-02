#include "BombBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundManager.h"

BombBullet::BombBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr),
	_flame(0)
{
	// 初期位置の設定
	Position = pos;

	// バレットタイプの設定
	_bulletType = BOMB_BULLET;

	// 発射したプレイヤーの保存
	_playerNum = plNum;

	// 進む方向
	_distVec = dist;

	// エフェクトインスタンスの作成
	_pEffect = std::make_shared<MyEffect>(BOMB_BULLET_EFFECT, pos);
}

BombBullet::~BombBullet()
{
	if (_flame == 0) {
		_pEffect->StopEffect();
	}
	else if (!_deadFlag) {
		_explosionEffect->StopEffect();
	}
}

void BombBullet::Update()
{
	if (!_collisionFlag && _flame == 0) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED") * 0.5f;
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	// 一定のラインを越えたら削除する
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	if (_flame > 0) {
		_explosionEffect->Update(Position);
		_flame++;
		if (_flame == 60) {
			_deadFlag = true;
			_explosionEffect->StopEffect();
		}
	}
	else {
		// マップとの当たり判定をとる
		if (_collManager->CollisionBullet(Position, 3.0f, BOMB_BULLET)) {

			SoundManager::GetInstance().RingSE(SE_EXPLOSION);

			_pEffect->StopEffect();
			_explosionEffect = std::make_shared<MyEffect>(BLOCK_DESTROY_EFFECT, Position);
			_flame = 1;
		}
	}

	// エフェクトの更新
	_pEffect->Update(Position);
}

void BombBullet::Draw() const
{
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0xf0ff00, 0xf0ff00, true);
}

#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include "Components.h"
#include <memory>

class BulletManager;
class MapBulletCollisionManager;
class BulletBase:
	public Transform
{
public:
	BulletBase();
	virtual ~BulletBase() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void UpdatePl() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// 死亡フラグを返す
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool IsDead() const;

	 /// <summary>
	 /// 自身の弾の種類を返す
	 /// </summary>
	 /// <returns>バレットマネージャーの定数</returns>
	 int GetBulletType() const;

	 /// <summary>
	 /// マップと当たったかどうかを返す現状グラップラーのみ判定
	 /// </summary>
	 /// <returns>当たっていたらtrue</returns>
	 bool GetCollisionFlag() const;

	 /// <summary>
	 /// 弾が無効かされているか返す現状グラップラーのみ
	 /// </summary>
	 /// <returns>無効であればtrue</returns>
	 bool GetInvalidFlag() const;

	 /// <summary>
	 /// 弾を無効化する
	 /// </summary>
	 void KillBullet();

	 /// <summary>
	 /// 自身がどのプレイヤーから発射されたかを返す
	 /// </summary>
	 /// <returns>プレイヤーナンバー</returns>
	 int GetPlayerNum();

protected:

	// 死亡フラグ
	bool _deadFlag;

	// 自身の弾の種類
	int _bulletType;

	// 当たったフラグ
	bool _collisionFlag;

	// 無効フラグ
	bool _invalidFlag;

	// 自身がどのプレイヤーから発射されたかを保存しておく
	int _playerNum;

	// 移動方向ベクトル
	Vec3 _distVec;

	// 重力
	float _gravity;

};


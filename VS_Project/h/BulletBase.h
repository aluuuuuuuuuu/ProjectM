#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include "Components.h"

class BulletBase:
	public Transform
{
public:
	BulletBase();
	virtual ~BulletBase() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

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
	 /// マップと当たったかどうかを返す
	 /// </summary>
	 /// <returns>当たっていたらtrue</returns>
	 bool GetCollisionFlag() const;
protected:

	// 死亡フラグ
	bool _deadFlag;

	// 自身の弾の種類
	int _bulletType;

	// 当たったフラグ
	bool _collisionFlag;

};


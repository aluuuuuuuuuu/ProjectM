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
protected:

	// 死亡フラグ
	bool _deadFlag;

};


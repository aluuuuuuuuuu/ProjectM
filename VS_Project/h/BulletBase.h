#pragma once
#include "Vec3.h"
#include "Constant.h"
#include "DxLib.h"
#include "Components.h"

class BulletBase:
	public Constant,
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

};


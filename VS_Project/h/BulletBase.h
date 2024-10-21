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
	/// XVˆ—
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	virtual void Draw() const = 0;

};


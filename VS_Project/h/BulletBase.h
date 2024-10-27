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
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// ���S�t���O��Ԃ�
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool IsDead() const;
protected:

	// ���S�t���O
	bool _deadFlag;

};


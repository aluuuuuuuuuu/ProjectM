#pragma once
#include "BulletBase.h"
#include <memory>
#include <list>

#define NORMAL_BULLET 0

class BulletBase;
class BulletManager
{
public:
	BulletManager();
	virtual ~BulletManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() const;

	void PushBullet(int bul, Vec3 dist, Vec3 pos);

	std::list<std::shared_ptr<BulletBase>> _pBullet;
private:
};

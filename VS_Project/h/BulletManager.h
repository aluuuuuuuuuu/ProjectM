#pragma once
#include "BulletBase.h"
#include <memory>
#include <list>
#include <Constant.h>

#define NORMAL_BULLET 0
#define GRAPPLER_BULLET 1

class MapBulletCollisionManager;
class BulletBase;
class BulletManager:
	public Constant
{
public:
	BulletManager(std::shared_ptr<MapBulletCollisionManager>& col);
	virtual ~BulletManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() const;

	/// <summary>
	/// プレイヤーが呼ぶ関数、指定の弾を発射する
	/// </summary>
	/// <param name="bul">弾の種類</param>
	/// <param name="dist">方向ベクトル</param>
	/// <param name="pos">座標</param>
	void PushBullet(int bul, Vec3 dist, Vec3 pos);

	/// <summary>
	/// 現状グラップラーが当たったかどうかを返す関数
	/// </summary>
	/// <returns>当たっていたらtrue</returns>
	bool IsCollisionBullet();

private:

	std::list<std::shared_ptr<BulletBase>> _pBullet;
	std::shared_ptr<MapBulletCollisionManager>& _collManager;
};

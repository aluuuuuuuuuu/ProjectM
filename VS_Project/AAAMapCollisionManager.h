#pragma once
#include "Components.h"
#include "Constant.h"
#include <vector>
#include <memory>


class StaticObjectManager;
class MapCollisionManager:
	public Constant
{
public:
	MapCollisionManager(CapsuleData& cap,StaticObjectManager& manager);
	virtual ~MapCollisionManager();

	// プレイヤーと静的オブジェクトの当たり判定をとって移動するベクトルを返す
	Vec3 PlayerCollision();

	// マップの当た判定のテスト表示
	void DrawColl();

	// 資格の描画
	void DrawBoxColl(Vec3 min, Vec3 max);

private:

	// カプセルとボックスの平面上の当たり判定をとる関数
	bool ColliosionBoxCapsuleParallel(Vec3 min, Vec3 max);

	// プレイヤーがずれる移動ベクトルを返す
	Vec3 CollisionMove(Vec3 min, Vec3 max);

	// プレイヤーのカプセルの情報
	CapsuleData& m_playerCapsule;

	// 静的オブジェクトマネージャーの参照
	StaticObjectManager& m_staticObjectManager;

	// プレイヤーの前フレームの座標
	CapsuleData m_beforePlayerPos;

	// 衝突しているすべての壁の移動ベクトル
	std::vector<Vec3> m_move;

	// 最終的な壁に対するコリジョンの移動ベクトル
	Vec3 m_lastMoveVec;
};


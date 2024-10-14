#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#include ""

MapCollisionManager::MapCollisionManager(CapsuleData& cap, StaticObjectManager& manager) :
	m_playerCapsule(cap),
	m_staticObjectManager(manager)
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/Collision.csv");
}

MapCollisionManager::~MapCollisionManager()
{

}

Vec3 MapCollisionManager::PlayerCollision()
{
	// 移動ベクトルを初期化する
	m_lastMoveVec = 0;
	m_move.clear();


	// プレイヤーとオブジェクトの当たり判定をとる
	for (auto obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// オブジェクトの種類を特定する
		if (obj->m_code == WALL_CODE) {

			// 角度に応じてボックスの最小値と最大値を作成する
			Vec3 min;
			Vec3 max;
			if (obj->Angle.y == 0.0f) {
				// ボックスの最小値と最大値を作成する
				min = Vec3{ pos.x - std::get<float>(Constants["WALL_SHORT"]),pos.y,pos.z - std::get<float>(Constants["WALL_LONG"]) };
				max = Vec3{ pos.x + std::get<float>(Constants["WALL_SHORT"]),pos.y + std::get<float>(Constants["WALL_HEIGHT"]),pos.z + std::get<float>(Constants["WALL_LONG"]) };
			}
			else {
				// ボックスの最小値と最大値を作成する
				min = Vec3{ pos.x - std::get<float>(Constants["WALL_LONG"]),pos.y,pos.z - std::get<float>(Constants["WALL_SHORT"]) };
				max = Vec3{ pos.x + std::get<float>(Constants["WALL_LONG"]),pos.y + std::get<float>(Constants["WALL_HEIGHT"]),pos.z + std::get<float>(Constants["WALL_SHORT"]) };
			}

			// 判定する
			if (ColliosionBoxCapsuleParallel(min, max)) {
				// あたっている

				// 判定外への移動ベクトルを作成して保存
				m_move.push_back(CollisionMove(min, max));
			}
			else {
				// 当たっていない
			}
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}

	// 保存したすべての移動ベクトルを足して最終的な移動ベクトルを作成する
	for (auto vec : m_move) {
		m_lastMoveVec += vec;
	}

	// カプセルのデータを保存しておく
	m_beforePlayerPos = m_playerCapsule;

	return m_lastMoveVec;
}

void MapCollisionManager::DrawColl()
{
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// オブジェクトの種類を特定する
		if (obj->m_code == WALL_CODE) {
			DrawBoxColl(Vec3(pos.x - std::get<float>(Constants["WALL_LONG"]), pos.y, pos.z - std::get<float>(Constants["WALL_SHORT"])),
				Vec3(pos.x + std::get<float>(Constants["WALL_LONG"]), pos.y + std::get<float>(Constants["WALL_HEIGHT"]), pos.z + std::get<float>(Constants["WALL_SHORT"])));
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}
}

void MapCollisionManager::DrawBoxColl(Vec3 min, Vec3 max)
{
	// 最小値からy軸
	DrawLine3D(min.VGet(), VECTOR{ min.x,max.y,min.z }, 0xff0000);

	// 最小値からx軸
	DrawLine3D(min.VGet(), VECTOR{ max.x,min.y,min.z }, 0xff0000);

	// 最小値からz軸
	DrawLine3D(min.VGet(), VECTOR{ min.x,min.y,max.z }, 0xff0000);

	// 最大値からy軸
	DrawLine3D(max.VGet(), VECTOR{ max.x,min.y,max.z }, 0xff0000);

	// 最大値からx軸
	DrawLine3D(max.VGet(), VECTOR{ min.x,max.y,max.z }, 0xff0000);

	// 最大値からz軸
	DrawLine3D(max.VGet(), VECTOR{ max.x,max.y,min.z }, 0xff0000);
}

bool MapCollisionManager::ColliosionBoxCapsuleParallel(Vec3 min, Vec3 max)
{
	// 四角形の中でプレイヤーの中心に最も近い点を計算
	float closestX = (std::max)(min.x, (std::min)(m_playerCapsule.PointA.x, max.x));
	float closestY = (std::max)(min.z, (std::min)(m_playerCapsule.PointA.z, max.z));

	// プレイヤーの中心と最も近い点との距離を計算
	float distanceX = m_playerCapsule.PointA.x - closestX;
	float distanceY = m_playerCapsule.PointA.z - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

	// 距離がプレイヤーの半径以内かを確認
	return distanceSquared <= (m_playerCapsule.Radius * m_playerCapsule.Radius);
}

Vec3 MapCollisionManager::CollisionMove(Vec3 min, Vec3 max)
{
	// 当たる直前にプレイヤーが箱に対してどの位置にいたのかを調べる
	// 四角形の中で直前のプレイヤーの中心に最も近い点を計算
	float closestX = (std::max)(min.x, (std::min)(m_beforePlayerPos.PointA.x, max.x));
	float closestY = (std::max)(min.z, (std::min)(m_beforePlayerPos.PointA.z, max.z));

	// 最近点からプレイヤーの中心へ向かう単位ベクトルを作成する
	Vec3 center = (Vec3{ m_beforePlayerPos.PointA.x,0.0f,m_beforePlayerPos.PointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized();

	// 最近点からプレイヤーの座標への距離を求める
	float length = (Vec3{ m_playerCapsule.PointA.x,0.0f,m_playerCapsule.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

	// 半径から前座標への距離を引いた値がめり込んだ分の距離になる
	length = m_playerCapsule.Radius - length;

	// 最近点からボックスの判定外への移動ベクトルを作成
	return center * length;

}





















// 線分を表現する構造体
struct LineSegment {
	Vector3 start, end;

	// コンストラクタ
	LineSegment() : start(Vector3()), end(Vector3()) {}
	LineSegment(const Vector3& start_, const Vector3& end_) : start(start_), end(end_) {}

	// 線分上の最近接点を計算
	Vector3 closestPointTo(const Vector3& point) const {
		Vector3 lineVec = end - start;
		Vector3 pointVec = point - start;
		float t = lineVec.dot(pointVec) / lineVec.lengthSquared();

		// tが0から1の範囲内に収まるようにする
		t = std::max(0.0f, std::min(1.0f, t));
		return start + lineVec * t;
	}
};

// カプセルを表現する構造体
struct Capsule {
	LineSegment lineSegment; // 中心線分
	float radius;            // カプセルの半径

	// コンストラクタ
	Capsule(const LineSegment& segment, float radius_) : lineSegment(segment), radius(radius_) {}
};

// AABB（Axis-Aligned Bounding Box）を表現する構造体
struct AABB {
	Vector3 min, max; // 最小点と最大点

	// コンストラクタ
	AABB(const Vector3& min_, const Vector3& max_) : min(min_), max(max_) {}
};

// AABB上の最近接点を求める関数
Vector3 ClosestPointOnAABB(const AABB& aabb, const Vector3& point) {
	Vector3 closestPoint;
	// X軸について判定
	closestPoint.x = std::max(aabb.min.x, std::min(point.x, aabb.max.x));
	// Y軸について判定
	closestPoint.y = std::max(aabb.min.y, std::min(point.y, aabb.max.y));
	// Z軸について判定
	closestPoint.z = std::max(aabb.min.z, std::min(point.z, aabb.max.z));
	return closestPoint;
}

// 線分とAABBの最短距離を計算する関数
float DistanceSquaredLineSegmentAABB(const LineSegment& segment, const AABB& aabb) {
	// 最小距離の2乗を初期化
	float minDistSq = FLT_MAX;

	// AABB内に線分の一点が含まれているかチェック
	Vector3 closestPointStart = ClosestPointOnAABB(aabb, segment.start);
	Vector3 closestPointEnd = ClosestPointOnAABB(aabb, segment.end);

	// 線分の開始点がAABB内にある場合
	if (closestPointStart.x == segment.start.x &&
		closestPointStart.y == segment.start.y &&
		closestPointStart.z == segment.start.z) {
		return 0.0f; // 距離はゼロ
	}

	// 線分の終了点がAABB内にある場合
	if (closestPointEnd.x == segment.end.x &&
		closestPointEnd.y == segment.end.y &&
		closestPointEnd.z == segment.end.z) {
		return 0.0f; // 距離はゼロ
	}

	// 線分の各端点からAABBへの距離を計算
	float distSqStart = (segment.start - closestPointStart).lengthSquared();
	float distSqEnd = (segment.end - closestPointEnd).lengthSquared();
	minDistSq = std::min(distSqStart, distSqEnd);

	// 線分上の他の点についてもチェック
	// 一般的には、AABB の各面に対する線分の最近接点を計算する必要があります。
	// ここでは簡略化のため、端点のみをチェックしています。
	// より正確な距離を求めるには、各面との交差をチェックする必要があります。

	return minDistSq;
}

// カプセルとAABBの当たり判定を行う関数
bool CheckCapsuleAABB(const Capsule& capsule, const AABB& aabb) {
	// カプセルの線分とAABBとの最短距離の2乗を計算
	float distanceSquared = DistanceSquaredLineSegmentAABB(capsule.lineSegment, aabb);

	// 距離がカプセルの半径以内かどうかを判定
	return distanceSquared <= (capsule.radius * capsule.radius);
}

#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#include <algorithm>

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
	Vec3 center =  (Vec3{ m_beforePlayerPos.PointA.x,0.0f,m_beforePlayerPos.PointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized()  ;

	// 最近点からプレイヤーの座標への距離を求める
	float length = (Vec3{ m_playerCapsule.PointA.x,0.0f,m_playerCapsule.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

	// 半径から前座標への距離を引いた値がめり込んだ分の距離になる
	length = m_playerCapsule.Radius - length;

	// 最近点からボックスの判定外への移動ベクトルを作成
	return center * length;

}

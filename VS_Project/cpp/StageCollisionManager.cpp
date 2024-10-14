#include "StageCollisionManager.h"
#include "StageManager.h"
#include <algorithm>

StageCollisionManager::StageCollisionManager(std::shared_ptr<StageManager>& stage) :
	_pStage(stage)
{
}

StageCollisionManager::~StageCollisionManager()
{
}

Vec3 StageCollisionManager::CapsuleCollision(CapsuleData data)
{
	// 移動ベクトルを初期化する
	_vResultMove = 0;
	_vAllMove.clear();

	Vec3 max,min;// 最大座標,最小座標

	// カプセルとステージの当たり判定を取る
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 2; b++) {
			for (int c = 0; c < 10; c++) {

				// 対象のボックスが存在した場合のみ判定する
				if (_pStage->GetStageInfo(a, b, c) != 0) {

					// ボックスの最大座標と最小座標を求める
					max = Vec3{ static_cast<float>(a * 10),static_cast<float>(b * 10),static_cast<float>(c * 10) };
					min = Vec3{ max - 10 };

					// 判定
					if (CollisionBoxCapsule(max, min, data)) {

						DrawString(10, 10, "atatta", 0xffff00);

						// ずらす分の移動ベクトルを作成
						Vec3 move = CreateMoveVector(max, min, data);

						// 配列に保存
						_vAllMove.push_back(move);

						// カプセルのデータも座標移動させておく
						data.PointA += move;
						data.PointB += move;
					}
				}
			}
		}
	}

	// 保存した全ての移動ベクトルを足して最終的な移動ベクトルを作成する
	for (auto vec : _vAllMove) {
		_vResultMove += vec;
	}

	// 最終的な移動ベクトルを返す
	return _vResultMove;
}

bool StageCollisionManager::CollisionBoxCapsule(Vec3 max, Vec3 min, CapsuleData data)
{
	// カプセルの線分とAABBとの最短距離の２乗を計算
	float distance = DistancePointToBox(data, max, min);

	// 距離がカプセルの半径以内かどうかを判定
	return distance <= (data.Radius * data.Radius);
}

float StageCollisionManager::DistancePointToBox(CapsuleData data, Vec3 max, Vec3 min)
{
	// 他の値と比較するために最大値で初期化する
	float minDist = FLT_MAX;

	// AABB内に線分が含まれているかチェックする
	Vec3 closetPointStart = ClosetPointBox(max, min, data.PointA);
	Vec3 closetPointEnd = ClosetPointBox(max, min, data.PointB);

	// 線分の開始点がAABB内にある場合
	if (closetPointStart.x == data.PointA.x &&
		closetPointStart.y == data.PointA.y &&
		closetPointStart.z == data.PointA.z) {
		return 0.0f;	// 距離はゼロ
	}

	// 線分の終了点がAABBないにある場合
	if (closetPointEnd.x == data.PointB.x &&
		closetPointEnd.y == data.PointB.y &&
		closetPointEnd.z == data.PointB.z) {
		return 0.0f;	// 距離はゼロ
	}

	// 線分の各端点からAABBへの距離を計算
	float distStart = (data.PointA - closetPointStart).SqLength();
	float distEnd = (data.PointB - closetPointEnd).SqLength();

	// 最小の値を求める
	minDist =(std::min)(distStart, distEnd);

	return minDist;
}

Vec3 StageCollisionManager::ClosetPointBox(Vec3 max, Vec3 min, Vec3 point)
{
	// 最近接点
	Vec3 closestPoint;

	// xyz軸について判定
	closestPoint.x = (std::max)(min.x, (std::min)(point.x, max.x));
	closestPoint.y = (std::max)(min.y, (std::min)(point.y, max.y));
	closestPoint.z = (std::max)(min.z, (std::min)(point.z, max.z));
	//DrawSphere3D(closestPoint.VGet(), 2, 8, 0xffff00, 0xffff00, true);

	return closestPoint;
}

Vec3 StageCollisionManager::CreateMoveVector(Vec3 max, Vec3 min, CapsuleData data)
{
	// 当たる直前にカプセルがボックスに対してどの位置にいたのかを調べる
	// ボックスの中で直前のカプセルの中心に最も近い点を算出
	Vec3 closestA,closestB,unit;
	float dist;

	closestA = ClosetPointBox(max, min, data.FrontPointA);
	closestB = ClosetPointBox(max, min, data.FrontPointB);

	// より近い方を求める
	if ((closestA - data.FrontPointA).Length() < (closestB - data.FrontPointB).Length()) {

		// Aのほうが近い場合
		// 最近接点からAまでの単位ベクトルを作成
		unit = (data.FrontPointA - closestA).GetNormalized();
		dist = (closestA - data.PointA).Length();
	}
	else {

		// Bのほうが近い場合
		// 最近接点からBまでの単位ベクトルを作成
		unit = (data.FrontPointB - closestB).GetNormalized();
		dist = (closestB - data.PointB).Length();
	}

	// あたっている面を判定して面と垂直方向以外の移動量をゼロにする
	// 中心方向にスライドしてしまうバグが起こってしまったための突貫工事
	if (std::abs(unit.x) > std::abs(unit.y) && std::abs(unit.x) > std::abs(unit.z)) {
		unit.y = 0;
		unit.z = 0;
	}
	else if (std::abs(unit.y) > std::abs(unit.x) && std::abs(unit.y) > std::abs(unit.z)) {
		unit.x = 0;
		unit.z = 0;
	}
	else {
		unit.x = 0;
		unit.y = 0;
	}

	// 半径から前座標への距離を引いた値がめり込んだ分の距離になる
	return (unit * (data.Radius - dist));
}

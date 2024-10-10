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

	Vec3 max;	// 最大頂点
	Vec3 min;	// 最低頂点

	// カプセルとステージの当たり判定を取る
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 2; b++) {
			for (int c = 0; c < 10; c++) {

				// 対象のボックスが存在した場合のみ判定する
				if (_pStage->GetStageInfo(a, b, c) != 0) {
					// ボックスの最大頂点を求める
					max = Vec3{ static_cast<float>(a * 10),static_cast<float>(b * 10),static_cast<float>(c * 10) };

					// ボックスの最低頂点を求める
					min = Vec3{ max - 10 };

					// 判定する
					if (CollisionBoxCapsule(max, min, data)) {
						DrawString(10, 10, "unko", 0xffffff);
						// あたっていた場合ずらす分の移動クトルを作成して保存する
						_vAllMove.push_back(CreateMoveVector(max, min, data));
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
	// カプセルの中心線分の最近接点を求める
	Vec3 lineDir = data.FrontPointB - data.FrontPointA;

	float lineLength = lineDir.SqLength();
	if (lineLength == 0.0f) {
		return DistancePointToBox(data.FrontPointA, max, min) <= data.Radius * data.Radius;
	}

	// カプセルの線分の最近接点をボックスに対してクランプ
	Vec3 pointOnLine;
	for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
		pointOnLine = data.FrontPointA + lineDir * t;
		if(DistancePointToBox(pointOnLine,max,min) <= data.Radius * data.Radius){
			return true;
		}
	}

	return false;
}

float StageCollisionManager::DistancePointToBox(Vec3 point, Vec3 max, Vec3 min)
{
	float dist = 0.0f;

	// 各軸にクランプして点がボックスの外にあるかを確認する
	if (point.x < max.x) {
		dist += (min.x - point.x) * (min.x - point.x);
	}
	else if (point.x > max.x) {
		dist += (point.x - max.x) * (point.x - max.x);
	}

	if (point.y < max.y) {
		dist += (min.y - point.y) * (min.y - point.y);
	}
	else if (point.y > max.y) {
		dist += (point.y - max.y) * (point.y - max.y);
	}

	if (point.z < max.z) {
		dist += (min.z - point.z) * (min.z - point.z);
	}
	else if (point.z > max.z) {
		dist += (point.z - max.z) * (point.z - max.z);
	}

	return dist;
}

Vec3 StageCollisionManager::CreateMoveVector(Vec3 max, Vec3 min, CapsuleData data)
{
	// 当たる直前にカプセルがボックスに対してどの位置にいたのかを調べる
	// ボックスの中で直前のカプセルの中心に最も近い点を算出
	Vec3 closest;
	closest.x = (std::max)(min.x, (std::min)(data.FrontPointA.x, max.x));
	closest.y = (std::max)(min.y, (std::min)(data.FrontPointA.y, max.y));
	closest.z = (std::max)(min.z, (std::min)(data.FrontPointA.z, max.z));

	// 最近接点から前フレームのカプセルの中心へ向かう単位ベクトルを作成する
	//Vec3 unitVec = ()
	return Vec3();
}

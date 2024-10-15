#pragma once
#include "Components.h"
#include <memory>


class StageCollisionManager;
class Player:
	public Transform,
	public CapsuleCollision
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player(std::shared_ptr<StageCollisionManager>& col);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// シーンから当たり判定した後の座標を設定する
	/// </summary>
	void SetPos(Vec3 pos);
private:

	/// <summary>
	/// コントローラー入力で移動ベクトルを作成する
	/// </summary>
	/// <returns>移動ベクトル</returns>
	Vec3 CreateMoveVec();

	/// <summary>
	/// ジャンプ力を返す
	/// </summary>
	/// <returns>ジャンプ力</returns>
	float CreateYMoveScale();

	/// <summary>
	/// 現在地上にいるか判定する
	/// </summary>
	/// <returns>true:地上にいる</returns>
	bool OnGround();

	// Y軸の移動量
	float _yMoveScale;

	// 地上に立っているフラグ
	bool _isGround;

	// 前フレームの座標
	Vec3 _frontPos;

	// 移動ベクトル
	Vec3 _moveVec;

	//  ステージコリジョンマネージャーの参照
	std::shared_ptr<StageCollisionManager>& _collManager;


};


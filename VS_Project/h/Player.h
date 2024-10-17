#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"

class PlayerCamera;
class StageCollisionManager;
class Player:
	public Transform,
	public CapsuleCollision,
	public Model,
	public Constant
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

	/// <summary>
	/// 引数のベクトルを引数の回転値に合わせてY軸回転させる
	/// </summary>
	/// <param name="vec">対象のベクトル</param>
	/// <param name="angle">Y軸の回転値</param>
	/// <returns>回転後のベクトル</returns>
	Vec3 RotateVec(Vec3 vec, float angle);

	/// <summary>
	/// 引数のベクトルの向きにY軸回転する
	/// </summary>
	/// <param name="moveVec">移動ベクトル</param>
	void RotateAngle(Vec3 moveVec);

	// Y軸の移動量
	float _MoveScaleY;

	// 地上に立っているフラグ
	bool _isGround;

	// 前フレームの座標
	Vec3 _frontPos;

	// 移動ベクトル
	Vec3 _moveVec;

	//  ステージコリジョンマネージャーの参照
	std::shared_ptr<StageCollisionManager>& _collManager;

	// カメラポインタ
	std::shared_ptr<PlayerCamera> _pCamera;
};


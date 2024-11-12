#pragma once
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"

class PlayerManager;
class BulletManager;
class PlayerCamera;
class Player:
	public Transform,
	public CapsuleCollision,
	public Model,
	public Animation
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// 移動などの処理
	/// </summary>
	void Control();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// カメラの座標をセットする
	/// </summary>
	void CameraSet() const;

	/// <summary>
	/// 地上フラグを入手する
	/// </summary>
	/// <returns>グラウンドフラグ<returns>
	bool GetGroundFlag() const;

private:

	/// <summary>
	/// 自身の回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動関数をまとめた関数
	/// </summary>
	void Move();
	
	/// <summary>
	/// 引数のラジアンに合わせてベクトルを回転させる
	/// </summary>
	/// <param name="vec">回転させるベクトル</param>
	/// <param name="angle">ラジアン</param>
	/// <returns>回転後のベクトル</returns>
	Vec3 RotateMoveVec(Vec3 vec,float angle);

	/// <summary>
	/// コントローラー入力で移動ベクトルを作成する
	/// </summary>
	/// <returns>移動ベクトル</returns>
	void CreateMoveVec();

	/// <summary>
	/// ジャンプ力を返す
	/// </summary>
	/// <returns>ジャンプ力</returns>
	void CreateYMoveScale();

	/// <summary>
	/// 現在地上にいるか判定する
	/// </summary>
	/// <returns>true:地上にいる</returns>
	bool OnGround();

	/// <summary>
	/// Y軸の回転値を引数の値に徐々に近づけていく
	/// </summary>
	/// <param name="targetAngle">目標の値</param>
	void RotateAngleY(float targetAngle);

	/// <summary>
	/// 2次元ベクトルを角度ごとに8つに分類する
	/// </summary>
	/// <returns>分類先</returns>
	int ClassifyDirection();

	/// <summary>
	/// アニメーション制御関数
	/// </summary>
	void AnimationContorol();

	// Y軸の移動量
	float _moveScaleY;

	// 地上に立っているフラグ
	bool _isGround;

	// 前フレームの座標
	Vec3 _frontPos;

	// 移動ベクトル
	Vec3 _moveVec;

	// Y軸が一定になったカウント
	int _groundCount;

	// バレットマネージャーの参照
	std::shared_ptr<BulletManager>& _bulletManager;

	// カメラポインタ
	std::shared_ptr<PlayerCamera> _pCamera;

	// 走っているフラグ
	bool _runFlag;

	// 使用するパッドのナンバー
	int _padNum;

	// プレイヤーマネージャーの参照
	PlayerManager& _manager;

	// 残段数
	int _bulletNum;

	// 向いている方向のベクトル
	Vec3 _forwardVec;

	// グラップラーフラグ
	bool _grapplerFlag;

	// グラップラー使用可能フラグ
	bool _grapplerAvailableFlag;

	// グラップラー発射中フラグ
	bool _grapplerUseFlag;

};


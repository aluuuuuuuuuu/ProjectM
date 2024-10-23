#pragma once
#include "Constant.h"
#include "Vec3.h"
#include "Components.h"

class PlayerCamera :
	public Constant,
	public Transform
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">プレイヤーの座標</param>
	PlayerCamera(Vec3 pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~PlayerCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="pos">プレイヤーの座標</param>
	void Update(Vec3 pos);


private:

	/// <summary>
	/// 回転
	/// </summary>
	/// <param name="pos">プレイヤーの座標</param>
	/// <returns>回転後の座標</returns>
	Vec3 Rotate(Vec3 pos);


	/// <summary>
	/// 引数の座標を回転させる
	/// </summary>
	/// <param name="pos">プレイヤーの座標</param>
	/// <returns>回転後の座標</returns> 
	Vec3 RotatePos(Vec3 pos);

	// カメラから発せられるライトハンドル
	int _lightHandle;
};


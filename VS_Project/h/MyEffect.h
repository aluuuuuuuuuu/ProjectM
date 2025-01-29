#pragma once
#include "Vec3.h"

class MyEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="effect">エフェクトキー</param>
	/// <param name="pos">初期位置</param>
	MyEffect(int effect, Vec3 pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MyEffect();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="pos">座標</param>
	void Update(Vec3 pos);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// エフェクトを停止する
	/// </summary>
	void StopEffect();


private:

	// プレイハンドル
	int _playHandle;
};


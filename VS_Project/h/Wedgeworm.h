#pragma once
#include "Components.h"

class Wedgeworm:
	public Transform,
	public Model,
	public Animation
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="num">ナンバー</param>
	Wedgeworm(int num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Wedgeworm();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
private:


};


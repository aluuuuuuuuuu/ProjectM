#pragma once
#include "Vec2.h"
#include "Vec3.h"

class SelectFinger
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="padNum">パッドナンバー</param>
	SelectFinger(int padNum);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SelectFinger();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// 今フレームでAボタンが押されたかどうか
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	bool IsPushButton() const;

	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <returns>二次元座標</returns>
	Vec2 GetPos() const;
private:

	// パッドナンバー
	int _padNum;

	// 最大プレイヤー数分の指画像ハンドル
	int _fingerHandle[4];

	// 表示座標
	Vec2 _pos;

	// 決定ボタンフラグ
	bool _pushButtonFlag;
};


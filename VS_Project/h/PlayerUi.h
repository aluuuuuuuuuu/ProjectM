#pragma once
#include "Vec2.h"
#include "PlayerManager.h"

class PlayerUi
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playerNum">プレイヤーの総数</param>
	PlayerUi(int playerNum);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerUi();

	/// <summary>
	/// 更新処理
	/// </summary>
	void UpdatePl();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="center">描画の中心座標</param>
	void Draw(Vec2 center, BulletData data) const;
private:

	/// <summary>
	/// 通常弾画像ハンドル
	/// </summary>
	int _normalBulletHandle;

	/// <summary>
	/// 爆発弾画像ハンドル
	/// </summary>
	int _bombBulletHandle;

	/// <summary>
	/// グラップル弾画像ハンドル
	/// </summary>
	int _grappleBulletHandle;

	/// <summary>
	/// レティクル画像ハンドル
	/// </summary>
	int _reticleHandle;

	/// <summary>
	/// アイコンフレーム画像ハンドル
	/// </summary>
	int _frameHandle;

	/// <summary>
	/// 画面中心からの描画余白
	/// </summary>
	Vec2 _drawMargin;

	/// <summary>
	/// アイコン同士の余白
	/// </summary>
	int _margin;

	/// <summary>
	/// 画像の拡大率
	/// </summary>
	double _exRate;

	/// <summary>
	/// フレームの描画座標
	/// </summary>
	Vec2 _framePos;

};


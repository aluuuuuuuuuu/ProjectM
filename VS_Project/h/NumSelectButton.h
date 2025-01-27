#pragma once
#include "Vec2.h"

class NumSelectButton
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	NumSelectButton();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NumSelectButton();

	/// <summary>
	/// 更新処理
	/// </summary>
	void UpdatePl();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// 選択人数を取得
	/// </summary>
	/// <returns>選択人数</returns>
	int GetSelectNum() const;

private:

	// 人数選択ボタン画像
	int _numHandle[4];

	// ゲーム終了ボタン
	int _gameEndHandle;

	// 選択矢印
	int _arrowHandle;

	// 矢印表示座標
	Vec2 _arrowPos;

	// 選択人数
	int _selectNum;
};


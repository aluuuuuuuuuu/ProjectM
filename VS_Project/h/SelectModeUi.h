#pragma once
#include "Vec2.h"

constexpr int SOLO_MODE = 0;
constexpr int MULTI_MODE = 1;
constexpr int TUTORIAL_MODE = 2;
constexpr int OPTION_MODE = 3;

class SelectModeUi
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectModeUi();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectModeUi();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
private:

	// 選択している項目の番号
	int _selectButtonNum;

	// 中央の円のハンドル
	int _circleHandle;

	// 中央の円の座標
	Vec2 _circlePos;

	double _circleAngle;

	// 各ボタンハンドル
	int _buttonHandle[3];

	// ボタンの座標
	Vec2 _buttonPos[3];

	// ボタンの拡大率
	double _buttonScale[3];

	// 下のメッセージハンドル
	int _messageHandle[3];

};


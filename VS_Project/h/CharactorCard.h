#pragma once
#include "Vec2.h"

class CharactorCard
{
public:
	CharactorCard(int charNum);
	virtual ~CharactorCard();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
private:

	// カード画像ハンドル
	int _cardHandle;

	int _cardSelectedRed;
	int _cardSelectedBlue;
	int _cardSelectedGreen;
	int _cardSelectedYellow;

	// カード描画座標
	Vec2 _pos;
};


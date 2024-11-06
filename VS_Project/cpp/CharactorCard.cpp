#include "CharactorCard.h"
#include "DxLib.h"

CharactorCard::CharactorCard(int charNum) :
	_cardHandle(0)
{
	// キャラ画像のロード
	switch (charNum)
	{
	case 1:
		_cardHandle = LoadGraph("data/image/Card1.png");
		_pos = Vec2{ 190,290 };
		break;
	case 2:
		_cardHandle = LoadGraph("data/image/Card2.png");
		_pos = Vec2{ 580,290 };
		break;
	case 3:
		_cardHandle = LoadGraph("data/image/Card3.png");
		_pos = Vec2{ 950,290 };
		break;
	case 4:
		_cardHandle = LoadGraph("data/image/Card4.png");
		_pos = Vec2{ 1360,290 };
		break;
	default:
		break;
	}

	// 選択後画像のロード
	{
		_cardSelectedRed = LoadGraph("data/image/CardSelectedRed.png");
		_cardSelectedBlue = LoadGraph("data/image/CardSelectedBlue.png");
		_cardSelectedGreen = LoadGraph("data/image/CardSelectedGreen.png");
		_cardSelectedYellow = LoadGraph("data/image/CardSelectedYellow.png");
	}
}

CharactorCard::~CharactorCard()
{
	DeleteGraph(_cardHandle);
}

void CharactorCard::Update()
{
}

void CharactorCard::Draw() const
{
	DrawGraph(_pos.intX(), _pos.intY(), _cardHandle, true);
	DrawGraph(_pos.intX() + 10, _pos.intY() + 10, _cardSelectedBlue, true);
}

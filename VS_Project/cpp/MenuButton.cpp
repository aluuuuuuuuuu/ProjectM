#include "MenuButton.h"
#include "DxLib.h"

MenuButton::MenuButton(Vec2 pos, Vec2 range, int handle, int type) :
	_pos(pos),
	_range(range),
	_graphHandle(handle),
	_type(type)
{
}

MenuButton::~MenuButton()
{
	DeleteGraph(_graphHandle);
}

void MenuButton::Update()
{
}

void MenuButton::Draw() const
{
	// ‰æ‘œ‚Ì•`‰æ
	DrawRotaGraph(_pos.intX(), _pos.intY(), 1.0, 0.0, _graphHandle, true);
}

Vec2 MenuButton::GetRange() const
{
	return Vec2{ _range.x / 2,_range.y / 2 };
}

Vec2 MenuButton::GetPos() const
{
	return _pos;
}

int MenuButton::GetType() const
{
	return _type;
}

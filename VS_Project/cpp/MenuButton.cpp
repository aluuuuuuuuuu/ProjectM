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

void MenuButton::Draw(int margin) const
{
	// ‰æ‘œ‚Ì•`‰æ
	DrawRotaGraph(_pos.intX(), _pos.intY() + margin, 1.0, 0.0, _graphHandle, true);
	DrawBox(_pos.intX() - GetRange().intX(), _pos.intY() - GetRange().intY(), _pos.intX() + GetRange().intX(), _pos.intY() + GetRange().intY(), 0xff0000, false);
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

void MenuButton::ChangeImage(int handle)
{
	_graphHandle = handle;
}

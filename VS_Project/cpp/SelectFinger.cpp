#include "SelectFinger.h"
#include "DxLib.h"
#include "Input.h"

SelectFinger::SelectFinger(int padNum) :
	_padNum(padNum),
	_selectFlag(false)
{
	_pos = Vec2{ 100,100 };
}

SelectFinger::~SelectFinger()
{
	for (auto& handle : _fingerHandle) {
		DeleteGraph(handle);
	}
}

void SelectFinger::Update()
{
	// 左スティックで移動
	Vec3 move;
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK,_padNum) >= 2000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, _padNum) * 10;

	}

	_pos += Vec2{ move.x,move.z * -1 };
}

void SelectFinger::Draw() const
{
	// 仮に円で表示する
	if (_padNum == 0) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0xff0000);
	}
	else if (_padNum == 1) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0x0000ff);
	}
	else if (_padNum == 2) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0x00ff00);
	}
	else if (_padNum == 3) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0xffff00);
	}
}


bool SelectFinger::IsPushButton(int button) const
{
	return  Input::GetInstance().IsTrigger(button, _padNum);
}

Vec2 SelectFinger::GetPos() const
{
	return _pos;
}

int SelectFinger::GetPadNum() const
{
	return _padNum;
}

void SelectFinger::SetSelectFlag(bool flag)
{
	_selectFlag = flag;
}

bool SelectFinger::IsSelected() const
{
	return _selectFlag;
}

void SelectFinger::SetSelectChara(int charaNum)
{
	_chara = charaNum;
}

int SelectFinger::GetSelectChara() const
{
	return _chara;
}

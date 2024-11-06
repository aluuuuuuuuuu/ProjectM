#include "SelectFinger.h"
#include "DxLib.h"
#include "Input.h"

SelectFinger::SelectFinger(int padNum) :
	_padNum(padNum),
	_pushButtonFlag(false)
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
	// ���X�e�B�b�N�ňړ�
	Vec3 move;
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK,_padNum) >= 2000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, _padNum) * 10;

	}

	// A�{�^���Ō���{�^���t���O�𗧂Ă�
	if (Input::GetInstance().IsTrigger(INPUT_A, _padNum)) {
		_pushButtonFlag = true;
	}
	else {
		_pushButtonFlag = false;
	}

	_pos += Vec2{ move.x,move.z * -1 };
}

void SelectFinger::Draw() const
{
	// ���ɉ~�ŕ\������
	if (_padNum == 0) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0xff0000);
	}
	else if (_padNum == 1) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0x00ff00);
	}
	else if (_padNum == 2) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0x0000ff);
	}
	else if (_padNum == 3) {
		DrawCircle(_pos.intX(), _pos.intY(), 30, 0xffff00);
	}
}

bool SelectFinger::IsPushButton() const
{
	return _pushButtonFlag;
}

Vec2 SelectFinger::GetPos() const
{
	return _pos;
}

#include "Player.h"
#include "DxLib.h"
#include "Input.h"

Player::Player()
{
	// �g��̐ݒ�
	Scale = Vec3{ 1.0f,1.0f,1.0f };

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,25.0f,0.0f };
}

Player::~Player()
{
}

void Player::Update()
{
	// �Ƃ肠�����ړ�
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		Position.x += 1;
	}

	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		Position.x -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_DOWN)) {
		Position.z -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_UP)) {
		Position.z += 1;
	}

	// �Ƃ肠��������
	Position.y -= 0.5;
}

void Player::Draw() const
{
	auto pos2 = VECTOR{ Position.x,Position.y + 10,Position.z };
	DrawCapsule3D(Position.VGet(), pos2, 3, 16, 0x00ff00, 0x00ff00, true);
}

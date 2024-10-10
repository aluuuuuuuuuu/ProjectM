#include "Player.h"
#include "DxLib.h"
#include "Input.h"

Player::Player()
{
	// �g��̐ݒ�
	Scale = Vec3{ 1.0f,1.0f,1.0f };

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// �J�v�Z���̏�����
	InitCapsule(Position, 10.0f, 10);
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
	if (Input::getInstance().IsHold(INPUT_A)) {
		Position.y -= 1;
	}
	if (Input::getInstance().IsHold(INPUT_Y)) {
		Position.y += 1;
	}

	//Position.y -= 0.5f;
	

	// �J�v�Z���ɍ��W��n��
	Set(Position);
}

void Player::Draw() const
{

	// �J�v�Z����`��
	DrawCapsule();
}

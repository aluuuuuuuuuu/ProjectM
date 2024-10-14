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
	InitCapsule(Position, 4.0f, 10);
}

Player::~Player()
{
}

void Player::Update()
{

	Vec3 move;
	// �Ƃ肠�����ړ�
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		move.x += 1;
	}

	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		move.x -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_DOWN)) {
		move.z -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_UP)) {
		move.z += 1;
	}

	// �Ƃ肠��������
	if (Input::getInstance().IsHold(INPUT_A)) {
		move.y -= 1;
	}
	if (Input::getInstance().IsHold(INPUT_Y)) {
		move.y += 1;
	}

	move.Normalize();

	Position += move;

	//Position.y -= 0.5f;
	

	// �J�v�Z���ɍ��W��n��
	Set(Position);
}

void Player::Draw() const
{

	// �J�v�Z����`��
	DrawCapsule();
}

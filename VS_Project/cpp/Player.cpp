#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "StageCollisionManager.h"

Player::Player(std::shared_ptr<StageCollisionManager>& col):
	_yMoveScale(0),
	_isGround(false),
	_collManager(col)
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
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// �ړ��x�N�g���̏�����
	_moveVec = 0;

	if (_isGround) DrawString(10, 30, "OnGround", 0xffffff);

	// ���W�Ɉړ��x�N�g�������Z����
	Position += CreateMoveVec();

	// �W�����v�Əd�͂𑫂������̂����W�ɑ���
	Position.y += CreateYMoveScale();

	// �R���W�����̔��������
	Position += _collManager->CapsuleCollision(_data);

	// �J�v�Z���ɍ��W��n��
	Set(Position);

	// �n��ɂ��邩���肷��
	_isGround = OnGround();

	_frontPos = Position;

}

void Player::Draw() const
{

	// �J�v�Z����`��
	DrawCapsule();
}

void Player::SetPos(Vec3 pos)
{
	Position = pos;
	Set(pos);
}

Vec3 Player::CreateMoveVec()
{
	// �ړ��ʂ�Ԃ��x�N�g��
	Vec3 move;

	// �Ƃ肠�����ړ�
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		move.x += 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		move.x -= 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_DOWN)) {
		move.z -= 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_UP)) {
		move.z += 1.0f;
	}

	return move.GetNormalized();
}

float Player::CreateYMoveScale()
{
	
	// �n��ɂ��Ȃ�������
	// ���̗������x�ɂȂ�܂ŗ������x���グ��
	//if (_isGround) {

	//}
	//else {

	if (_yMoveScale > -1.5f) {
		_yMoveScale -= 0.1f;
	}
	//}

	// A�{�^���ŃW�����v
	if (Input::getInstance().IsHold(INPUT_A) && _isGround) {

		// �W�����v�͂�^����
		_yMoveScale = 2.0f;
	}

	return _yMoveScale;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		return true;
	}

	return false;
}

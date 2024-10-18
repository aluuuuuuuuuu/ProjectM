#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "StageCollisionManager.h"
#include "PlayerCamera.h"

Player::Player(std::shared_ptr<StageCollisionManager>& col) :
	_moveScaleY(0),
	_isGround(false),
	_collManager(col),
	_groundCount(0),
	_runFlag(false)
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Player.csv");

	// �g��̐ݒ�
	Scale = Vec3{ 0.12f,0.12f,0.12f };

	// ���f���̏�������
	InitModel(MV1LoadModel("data/model/Player1.mv1"));

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// �J�v�Z���̏�����
	InitCapsule(Position, 3.0f, 12);

	// �J�����̍쐬
	_pCamera = std::make_shared<PlayerCamera>(Position);
}

Player::~Player()
{
}

void Player::Update()
{
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f angleY:%f", Position.x, Position.y, Position.z, Angle.y);

	// �ړ��x�N�g���̏�����
	_moveVec = 0;

	if (_isGround) DrawString(10, 30, "OnGround", 0xffffff);

	// �ړ�
	Move();

	// ���g�̉�]�l���X�V����
	Rotate();

	// �����蔻��
	Collision();

	// �n��ɂ��邩���肷��
	_isGround = OnGround();

	_frontPos = Position;

	// �J�����̍X�V
	_pCamera->Update(Position);

	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

void Player::Draw() const
{
#ifdef _DEBUG
	// �J�v�Z����`��
	DrawCapsule();
#endif // DEBUG

	DrawModel();
}

void Player::Rotate()
{
	// �������̓J�����Ɠ�������������
	if (!_runFlag) {
		RotateAngleY(_pCamera->Angle.y);
	}
	// ���蒆�͈ړ�����������
	else {

		float targetAngle;

		// �ړ���������̊p�x�����߂�
		Vec3 targetPos = Position + _moveVec;
		float x = targetPos.x - Position.x;
		float z = targetPos.z - Position.z;
		targetAngle = atan2f(x, z);
		targetAngle = targetAngle + static_cast<float>(DX_PI);
		DX_TWO_PI;

		RotateAngleY(targetAngle);
	}
}

void Player::Move()
{
	// xz�������̈ړ�
	CreateMoveVec();

	// Y�������̈ړ�
	CreateYMoveScale();

	// �ړ��x�N�g����y����]������
	RotateMoveVec();

	// ���W�Ɉړ��x�N�g���𑫂�
	Position += _moveVec;
}

void Player::Collision()
{
	// �J�v�Z���ɍ��W��n��
	Set(Position);

	// �R���W�����̔��������
	Position += _collManager->CapsuleCollision(_data);

	// �J�v�Z���ɍ��W��n��
	Set(Position);
}

void Player::CreateMoveVec()
{
	// �ړ��ʂ�Ԃ��x�N�g��
	Vec3 move;

	// �X�e�B�b�N�̓��͒l���ړ��x�N�g���ɑ������
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > 3000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, INPUT_PAD_1);
	}

	_moveVec += move;
}

void Player::CreateYMoveScale()
{

	// �n��ɂ��Ȃ�������
	// ���̗������x�ɂȂ�܂ŗ������x���グ��
	if (_isGround) {
		//_moveScaleY = 0.1f;
	}
	else {

		if (_moveScaleY > -1.5f) {
			_moveScaleY -= 0.1f;
		}
	}

	// A�{�^���ŃW�����v
	if (Input::GetInstance().IsHold(INPUT_A, INPUT_PAD_1) && _isGround) {

		// �W�����v�͂�^����
		_moveScaleY = 2.0f;
	}

	_moveVec.y += _moveScaleY;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		if (_groundCount == 0) {
			_groundCount++;
		}
		else {
			return true;
		}
	}
	else {
		_groundCount = 0;
	}

	return false;
}

void Player::RotateMoveVec()
{
	// Y����]�s��ɕϊ�
	MATRIX rotaMtx = MGetRotY(_pCamera->Angle.y);

	_moveVec = Vec3{ _moveVec.x * -1, _moveVec.y, _moveVec.z * -1 };

	// �ړ��x�N�g������]�l�ɍ��킹��Y����]������
	_moveVec = VTransform(_moveVec.VGet(), rotaMtx);
}

void Player::RotateAngleY(float targetAngle)
{
	// ���s�ړ��x�N�g����0����Ȃ��Ƃ������p�x���v�Z����
	if (_moveVec.x != 0.0f && _moveVec.z != 0.0f) {
		// �ړ���������ɏ��X�ɉ�]����

		// �����ړ��ʂ�菬�����Ȃ�����ڕW�̒l��������
		if (fabsf(Angle.y - targetAngle) > GetConstantFloat("ANGLE_ROTATE_SCALE")) {
			// ���₷�̂ƌ��炷�̂łǂ��炪�߂������f����
			float add = targetAngle - Angle.y;	// �����ꍇ�̉�]��
			if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// �����ꍇ�̉�]�ʂ����̐��������ꍇ���K������
			float sub = static_cast<float>(DX_TWO_PI) - add;	// �����ꍇ�̉�]��

			// ��]�ʂ��ׂď��Ȃ�����I������
			if (add < sub) {
				Angle.y += GetConstantFloat("ANGLE_ROTATE_SCALE");
			}
			else {
				Angle.y -= GetConstantFloat("ANGLE_ROTATE_SCALE");
			}

			// �����ɂ���Ĕ͈͊O�ɂȂ����ꍇ�̐��K��
			Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
			if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
		}
		else {
			Angle.y = targetAngle;
		}
	}
}

void Player::RotateAngleToCamera()
{
	float targetAngle = _pCamera->Angle.y;

	RotateAngleY(targetAngle);
}

void Player::RotateAngleToVec()
{

	float targetAngle = Angle.y;

	RotateAngleY(targetAngle);
}

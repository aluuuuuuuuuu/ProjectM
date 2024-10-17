#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "StageCollisionManager.h"
#include "PlayerCamera.h"

Player::Player(std::shared_ptr<StageCollisionManager>& col) :
	_MoveScaleY(0),
	_isGround(false),
	_collManager(col)
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Player.csv");

	// �g��̐ݒ�
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// ���f���̏�������
	InitModel(MV1LoadModel("data/model/MainActor.mv1"));

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// �J�v�Z���̏�����
	InitCapsule(Position, 4.0f, 10);

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

	// xz�������̈ړ�
	_moveVec += CreateMoveVec();

	// Y�������̈ړ�
	_moveVec.y += CreateYMoveScale();

	// �ړ��x�N�g����y����]������
	_moveVec = RotateVec(_moveVec, _pCamera->Angle.y);

	// ���W�Ɉړ��x�N�g���𑫂�
	Position += _moveVec;

	// ���g�̉�]�l���X�V����
	RotateAngle(_moveVec);

	// �R���W�����̔��������
	Position += _collManager->CapsuleCollision(_data);

	// �J�v�Z���ɍ��W��n��
	Set(Position);

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

	//DrawModel();
}

Vec3 Player::CreateMoveVec()
{
	// �ړ��ʂ�Ԃ��x�N�g��
	Vec3 move;

	// �X�e�B�b�N�̓��͒l���ړ��x�N�g���ɑ������
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK,INPUT_PAD_1) > 3000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, INPUT_PAD_1);
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

	if (_MoveScaleY > -1.5f) {
		_MoveScaleY -= 0.1f;
	}
	//}

	// A�{�^���ŃW�����v
	if (Input::GetInstance().IsHold(INPUT_A, INPUT_PAD_1) && _isGround) {

		// �W�����v�͂�^����
		_MoveScaleY = 2.0f;
	}

	return _MoveScaleY;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		return true;
	}

	return false;
}

Vec3 Player::RotateVec(Vec3 vec, float angle)
{
	// Y����]�s��ɕϊ�
	MATRIX rotaMtx = MGetRotY(angle);

	vec = Vec3{ vec.x * -1 , vec.y,vec.z * -1 };

	// �ړ��x�N�g������]�l�ɍ��킹��Y����]������
	vec = VTransform(vec.VGet(), rotaMtx);

	return vec;
}

void Player::RotateAngle(Vec3 moveVec)
{

	float targetAngle = Angle.y;

	// �ړ��x�N�g����0����Ȃ��Ƃ������p�x���v�Z����
	if (moveVec.x != 0.0f && moveVec.z != 0.0f) {
		// �ړ���������̊p�x�����߂�
		Vec3 targetPos = Position + moveVec;
		float x = targetPos.x - Position.x;
		float z = targetPos.z - Position.z;
		targetAngle = atan2f(x, z);
		targetAngle = targetAngle + static_cast<float>(DX_PI);
		DX_TWO_PI;

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

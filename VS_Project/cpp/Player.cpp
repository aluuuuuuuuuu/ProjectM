#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "NormalBullet.h"
#include "BulletManager.h"
#include "BulletBase.h"
#include "PlayerManager.h"

Player::Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum) :
	_moveScaleY(0),
	_isGround(false),
	_bulletManager(bullet),
	_groundCount(0),
	_runFlag(false),
	_padNum(padNum),
	_manager(manager),
	_bulletNum(15),
	_grapplerFlag(false),
	_grapplerAvailableFlag(true),
	_grapplerUseFlag(false)
{
	// �g��̐ݒ�
	Scale = Vec3{ 0.12f,0.12f,0.12f };

	// ���f���̏�������
	InitModel(_manager.GetModelHandle(padNum));

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// �J�v�Z���̏�����
	InitCapsule(Position, 3.0f, 12);

	// �A�j���[�V�����̏�������
	InitAnimation(_modelHandle, _manager.GetConstantInt("ANIM_AIMING_IDLE"), _manager.GetConstantFloat("BLEND_RATE"));

	// �J�����̍쐬
	_pCamera = std::make_shared<PlayerCamera>(Position, _padNum, _forwardVec);
}

Player::~Player()
{
}

void Player::Control()
{
	// �e�𔭎˂���
	if (Input::GetInstance().IsTrigger(INPUT_RIGHT_TRIGGER, _padNum) && _bulletNum > 0) {

		// ���˂�����W
		Vec3 pos = { Position.x  ,Position.y + 10 ,Position.z };

		if (_grapplerFlag) {
			if (_grapplerAvailableFlag) {
				_grapplerUseFlag = true;
				_grapplerAvailableFlag = false;
				// �e�𐶐�
				_bulletManager->PushBullet(GRAPPLER_BULLET, _forwardVec, pos);
			}

				
			
		}
		else {

			// ���Ƃ��ɑ����Ă���������ɂ���
			if (_runFlag) {
				_runFlag = false;
			}

			// �e�𐶐�
			_bulletManager->PushBullet(NORMAL_BULLET, _forwardVec, pos);

			_bulletNum--;
		}
	}

	// �O���b�v���[���������Ă��邩��m��ׂ�
	if (_bulletManager->IsCollisionBullet()) {
		// �������Ă����������ƃO���b�v���[�̕����Ɉړ��x�N�g����^����
	}



	// �O���b�v���[�̐؂�ւ�
	if (Input::GetInstance().IsTrigger(INPUT_RIGHT_SHOULDER, _padNum)) {
		if (_grapplerFlag) {
			if (!_grapplerUseFlag) {
				_grapplerFlag = false;
			}
		}
		else {
			_grapplerFlag = true;
		}
	}







	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::GetInstance();
	// �E�X�e�B�b�N�ŉ�]
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK, _padNum) > 3000) {

		// �X�e�B�b�N���X���������̉�]�̒l�𑝌�������
		if (input.GetStickVector(INPUT_RIGHT_STICK, _padNum).x != 0) {
			Angle.y += 0.000001 * (input.GetStickThumbX(INPUT_RIGHT_STICK, _padNum));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK, _padNum).z != 0) {
			Angle.z += 0.000001 * (input.GetStickThumbY(INPUT_RIGHT_STICK, _padNum));
		}

		// ���W�A���p�𐳋K������
		Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
		if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
	}

	// �ő�l�ƍŒ�l�𒲐�����
	if (Angle.z <= -0.9) {
		Angle.z = -0.9;
	}
	else if (Angle.z >= 0.9) {
		Angle.z = 0.9;
	}

	// �����[�h
	if (Input::GetInstance().IsTrigger(INPUT_X, _padNum)) {
		_bulletNum = 15;
	}

	// �ړ��x�N�g���̏�����
	_moveVec = 0;

	// �ړ�
	Move();

	// ���g�̉�]�l���X�V����
	Rotate();

	// �J�v�Z���ɍ��W��n��
	Set(Position);
}

void Player::Update()
{
	// �J�v�Z���ɍ��W��n��
	Set(Position);

	// �n��ɂ��邩���肷��
	_isGround = OnGround();

	_frontPos = Position;

	// �����Ă�������̃x�N�g�������߂�
	_forwardVec.x = std::cos(Angle.y * -1) * std::cos(Angle.z); // X����
	_forwardVec.y = std::sin(Angle.z);                 // Y�����i�㉺�����̉e���j
	_forwardVec.z = std::sin(Angle.y * -1) * std::cos(Angle.z); // Z����


	MATRIX aa;

	//aa = MGetRotX(Angle.z);
	//_forwardVec = VTransform(_forwardVec.VGet(), aa);


	// �J�����̍X�V
	_pCamera->Update(Position, _forwardVec, Angle);

	// �A�j���[�V�����R���g���[��
	AnimationContorol();

	// �A�j���[�V�����̍X�V
	if (_runFlag && _isGround) {

		// �����Ă���Ƃ��̃A�j���[�V�������x�ōX�V����
		UpdateAnimation(_modelHandle, _manager.GetConstantFloat("ANIM_SPEED_RUN"));
	}
	else {

		// ����
		UpdateAnimation(_modelHandle, _manager.GetConstantFloat("ANIM_SPEED_WALK"));
	}

	Transform trans;
	trans.Scale = Scale;
	trans.Position = Position;
	trans.Angle = Vec3{ Angle.x,Angle.y - 1.5708f,Angle.z };

	// ���f���̍X�V
	UpdateModel(trans);
}

void Player::Draw() const
{

#ifdef _DEBUG
	//�J�v�Z����`��
	DrawCapsule();
	DrawLine3D(Position.VGet(), (Position + _forwardVec * 20).VGet(), 0x00ffff);
	//DrawLine3D(Position.VGet(), (Position + Angle.GetNormalized() *20).VGet(), 0x00ffff);
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f angleY:%f angleZ:%f", Position.x, Position.y, Position.z, Angle.y, Angle.z);
#endif // DEBUG
	DrawModel();


	DrawCircle(1920 / 2, 1080 / 2, 10, 0xffff00);
}

void Player::CameraSet() const
{
	SetCameraPositionAndTarget_UpVecY(_pCamera->Position.VGet(), _pCamera->GetTarget().VGet());
}

bool Player::GetGroundFlag() const
{
	return _isGround;
}

void Player::Rotate()
{
	// �������̓J�����Ɠ�������������
	if (!_runFlag) {
		//RotateAngleY(_pCamera->Angle.y);
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

	//// X�{�^���Ń_�b�V���؂�ւ�
	//if (Input::GetInstance().IsTrigger(INPUT_X, _padNum)) {
	//	_runFlag = !_runFlag;
	//}

	// xz�������̈ړ�
	CreateMoveVec();

	// Y�������̈ړ�
	CreateYMoveScale();

	// �ړ��x�N�g����y����]������
	_moveVec = RotateMoveVec(_moveVec, Angle.y);

	// ���W�Ɉړ��x�N�g���𑫂�
	Position += _moveVec;
}

Vec3 Player::RotateMoveVec(Vec3 vec, float angle)
{
	Vec3 ret = vec;

	angle -= 1.5708f;

	// Y����]�s��ɕϊ�
	MATRIX rotaMtx = MGetRotY(angle);

	ret = Vec3{ vec.x * -1, vec.y, vec.z * -1 };

	// �ړ��x�N�g������]�l�ɍ��킹��Y����]������
	ret = VTransform(ret.VGet(), rotaMtx);

	return ret;
}

void Player::CreateMoveVec()
{
	// �ړ��ʂ�Ԃ��x�N�g��
	Vec3 move;

	// �X�e�B�b�N�̓��͒l���ړ��x�N�g���ɑ������
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, _padNum) > 3000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, _padNum);
	}

	if (_runFlag) {
		_moveVec += move * _manager.GetConstantFloat("RUN_SPEED");
	}
	else {
		_moveVec += move * _manager.GetConstantFloat("WALK_SPEED");
	}

	DrawFormatString(30, 50, 0xffffff, "%f %f %f", _moveVec.x, _moveVec.y, _moveVec.x);
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
	if (Input::GetInstance().IsHold(INPUT_A, _padNum) && _isGround) {

		// �W�����v�͂�^����
		_moveScaleY = 2.0f;

		// �W�����v�̊J�n�A�j���[�V�������Đ�
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_JUMP_UP"), false, _manager.GetConstantFloat("BLEND_RATE"));
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

void Player::RotateAngleY(float targetAngle)
{
	// ���s�ړ��x�N�g����0����Ȃ��Ƃ������p�x���v�Z����
	if (_moveVec.x != 0.0f && _moveVec.z != 0.0f) {
		// �ړ���������ɏ��X�ɉ�]����

		// �����ړ��ʂ�菬�����Ȃ�����ڕW�̒l��������
		if (fabsf(Angle.y - targetAngle) > _manager.GetConstantFloat("ANGLE_ROTATE_SCALE")) {
			// ���₷�̂ƌ��炷�̂łǂ��炪�߂������f����
			float add = targetAngle - Angle.y;	// �����ꍇ�̉�]��
			if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// �����ꍇ�̉�]�ʂ����̐��������ꍇ���K������
			float sub = static_cast<float>(DX_TWO_PI) - add;	// �����ꍇ�̉�]��

			// ��]�ʂ��ׂď��Ȃ�����I������
			if (add < sub) {
				Angle.y += _manager.GetConstantFloat("ANGLE_ROTATE_SCALE");
			}
			else {
				Angle.y -= _manager.GetConstantFloat("ANGLE_ROTATE_SCALE");
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

int Player::ClassifyDirection()
{
	// �L�����N�^�[�̌����ɍ��킹�Ĉړ��x�N�g������]
	float rotatedX = _moveVec.x * cos(Angle.y) - _moveVec.z * sin(Angle.y);
	float rotatedZ = _moveVec.x * sin(Angle.y) + _moveVec.z * cos(Angle.y);

	float angle = atan2(rotatedX, rotatedZ);

	// 45�x�i��/4�j���Ƃɕ����𕪗�
	if (angle >= -DX_PI / 8 && angle < DX_PI / 8) {
		return 0;  // �O
	}
	else if (angle >= DX_PI / 8 && angle < 3 * DX_PI / 8) {
		return 1;  // �O�E
	}
	else if (angle >= 3 * DX_PI / 8 && angle < 5 * DX_PI / 8) {
		return 2;  // �E
	}
	else if (angle >= 5 * DX_PI / 8 && angle < 7 * DX_PI / 8) {
		return 3;  // ��E
	}
	else if ((angle >= 7 * DX_PI / 8 && angle <= DX_PI) || (angle < -7 * DX_PI / 8 && angle >= -DX_PI)) {
		return 4;  // ��
	}
	else if (angle >= -7 * DX_PI / 8 && angle < -5 * DX_PI / 8) {
		return 5;  // �㍶
	}
	else if (angle >= -5 * DX_PI / 8 && angle < -3 * DX_PI / 8) {
		return 6;  // ��
	}
	else if (angle >= -3 * DX_PI / 8 && angle < -DX_PI / 8) {
		return 7;  // �O��
	}

	return 0;  // �f�t�H���g�͑O
}

void Player::AnimationContorol()
{
	// �n�ʂɂ��Ă��Ȃ��Ƃ�
	if (!_isGround) {
		// �W�����v�A�b�v�A�j���[�V�����o�Ȃ���΃��[�v�A�j���[�V�������Đ�����
		if (GetAnimTag() != _manager.GetConstantInt("ANIM_JUMP_UP")) {
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_JUMP_LOOP"), true, _manager.GetConstantFloat("BLEND_RATE"));
		}
		return;
	}

	if (_moveVec.x == 0.0f && _moveVec.z == 0.0f) {
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_AIMING_IDLE"), true, _manager.GetConstantFloat("BLEND_RATE"));
		return;
	}

	int dir = ClassifyDirection();

	// �����Ă���
	if (_runFlag) {

		// ��ɑ����Ă���A�j���[�V����
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
	}
	// �����Ă���
	else {
		// �����ɑΉ�����A�j���[�V�������Đ�
		switch (dir) {
		case 0:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 1:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 2:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 3:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 4:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 5:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 6:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 7:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));			break;
		}
	}
}

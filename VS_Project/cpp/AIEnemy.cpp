#include "AIEnemy.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "NormalBullet.h"
#include "BulletManager.h"
#include "BulletBase.h"
#include "PlayerManager.h"

AIEnemy::AIEnemy(std::shared_ptr<BulletManager>& bullet, BulletData& data) :
	_moveScaleY(0),
	_groundFlag(false),
	_bulletManager(bullet),
	_groundCount(0),
	_grapplerScale(0),
	_deadFlag(false),
	_bulletData(data)
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

	// �o���b�g�f�[�^�̏�����
	// �N�[���^�C���̏�����
	for (auto& time : _bulletData._bullletCoolTime) {
		time = 0;
	}

	// �I�����Ă���e�̏�����
	_bulletData._selectBullet = NORMAL_BULLET;
}

AIEnemy::~AIEnemy()
{
}

void AIEnemy::Control()
{
}

void AIEnemy::Update()
{
	// �J�v�Z���ɍ��W��n��
	Set(Position);

	// �O��y���W�ƍ���y���W�������ł���Β��n���Ă���
	if (_frontPos.y == Position.y) {
		if (_groundCount == 0) {
			_groundCount++;
		}
		else {
			_groundFlag = true;
		}
	}
	else {
		_groundCount = 0;
		_groundFlag = false;
	}

	// �O�t���[���̍��W��ۑ�����
	_frontPos = Position;

	// �������x�������Â�������
	if (!_groundFlag && _moveScaleY > -1.5f) {
		_moveScaleY -= 0.1f;
	}

	// �����Ă�������̃x�N�g�������߂�
	_forwardVec.x = std::cos(Angle.y * -1) * std::cos(Angle.z); // X����
	_forwardVec.y = std::sin(Angle.z);                 // Y�����i�㉺�����̉e���j
	_forwardVec.z = std::sin(Angle.y * -1) * std::cos(Angle.z); // Z����

	// �O���b�v���[�̈ړ�����
	if (_groundFlag) {
		_grapplerScale = 0.0f;
	}
	else if (_grapplerScale <= 0.0f) {
		_grapplerScale = 0.0f;
	}
	else {
		_grapplerScale -= 0.01f;
	}

	// �O���b�v���[���������Ă��邩��m��ׂ�
	if (_bulletManager->IsCollisionBullet(_padNum) && !_bulletManager->GetInvalidFlag(_padNum)) {

		// �e�̖�����
		_bulletManager->KillBullet(_padNum);

		// �������Ă����������ƃO���b�v���[�̕����Ɉړ��x�N�g����^����
		if (_groundFlag) {
			_moveScaleY = 2.4f;
		}
		else {
			_moveScaleY = 1.5f;
		}

		// �O���b�v���[�Ɍ������P�ʃx�N�g�����쐬����
		_grapplerUnitVec = (_bulletManager->GetBulletPos(_padNum) - Position).GetNormalized();

		// �O���b�v���[�̒��e�_�ւ̋����ɂ���Ĉړ����x��ω�������
		_grapplerScale = 0.02f * (_bulletManager->GetBulletPos(_padNum) - Position).Length();

		// �O���b�v���[�ɂ��ړ����x�̍ő�l�����߂�
		if (_grapplerScale > 1.8f) {
			_grapplerScale = 1.8f;
		}
	}

	// �A�j���[�V�����R���g���[��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
	AnimationContorol();

	// �A�j���[�V�����̍X�V
	UpdateAnimation(_modelHandle, _manager.GetConstantFloat("ANIM_SPEED_WALK"));

	// ���f���p�̃g�����X�t�H�[�����쐬����
	Transform trans;
	trans.Scale = Scale;
	trans.Position = Position;
	trans.Angle = Vec3{ Angle.x,Angle.y - 1.5708f,Angle.z };

	// ���f���̍X�V
	UpdateModel(trans);
}

void AIEnemy::Draw() const
{
	// ���f���̕`��
	DrawModel();
}

bool AIEnemy::GetGroundFlag() const
{
	return _groundFlag;
}

bool AIEnemy::GetDeadFlag() const
{
	return _deadFlag;
}

void AIEnemy::KillPlayer()
{
	_deadFlag = true;
}

void AIEnemy::RotateAngleY(float targetAngle)
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

int AIEnemy::ClassifyDirection()
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

void AIEnemy::AnimationContorol()
{
	// �n�ʂɂ��Ă��Ȃ��Ƃ�
	if (!_groundFlag) {
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
	// �����ɑΉ�����A�j���[�V�������Đ�
	switch (dir) {
	case 0:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 1:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 2:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 3:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 4:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 5:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 6:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	case 7:
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
		break;
	}
}

void AIEnemy::BulletTrigger()
{
	// ���˂�����W
	Vec3 pos = { Position.x  ,Position.y + 10 ,Position.z };

	switch (_bulletData._selectBullet)
	{
	case NORMAL_BULLET:
		if (_bulletData._bullletCoolTime[NORMAL_BULLET] == 0) {
			// �e�𐶐�
			_bulletManager->PushBullet(NORMAL_BULLET, _forwardVec, pos, _padNum);

			// �N�[���^�C����ݒ肷��
			_bulletData._bullletCoolTime[NORMAL_BULLET] = 30;
		}
		break;
	case GRAPPLER_BULLET:
		if (_bulletData._bullletCoolTime[GRAPPLER_BULLET] == 0) {
			// �e�𐶐�
			_bulletManager->PushBullet(GRAPPLER_BULLET, _forwardVec, pos, _padNum);

			// �N�[���^�C����ݒ肷��
			_bulletData._bullletCoolTime[GRAPPLER_BULLET] = 1200;
		}
		break;
	case BOMB_BULLET:
		if (_bulletData._bullletCoolTime[BOMB_BULLET] == 0) {
			// �e�𐶐�
			_bulletManager->PushBullet(BOMB_BULLET, _forwardVec, pos, _padNum);

			// �N�[���^�C����ݒ肷��
			_bulletData._bullletCoolTime[BOMB_BULLET] = 300;
		}
		break;
	default:
		break;
	}
}

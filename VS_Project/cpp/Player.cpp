#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "NormalBullet.h"
#include "BulletManager.h"
#include "BulletBase.h"
#include "PlayerManager.h"
#include "EffectManager.h"
#include "MyEffect.h"
#include "SoundManager.h"

Player::Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum, BulletData& data) :
	_moveScaleY(0),
	_groundFlag(false),
	_bulletManager(bullet),
	_groundCount(0),
	_padNum(padNum),
	_manager(manager),
	_grapplerScale(0),
	_deadFlag(false),
	_bulletData(data),
	_frame(0)
{
	// �֐��|�C���^�̏�����
	_controlFunc = &Player::ControlPl;
	_updateFunc = &Player::UpdatePl;

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

	// �o���b�g�f�[�^�̏�����
	// �N�[���^�C���̏�����
	for (auto& time : _bulletData._bullletCoolTime) {
		time = 0;
	}

	// �I�����Ă���e�̏�����
	_bulletData._selectBullet = NORMAL_BULLET;
}

Player::Player(std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, BulletData& data) :
	_moveScaleY(0),
	_groundFlag(false),
	_bulletManager(bullet),
	_groundCount(0),
	_manager(manager),
	_grapplerScale(0),
	_deadFlag(false),
	_bulletData(data),
	_frame(0),
	_padNum(1)
{
	// �֐��|�C���^�̏�����
	_controlFunc = &Player::ControlAI;
	_updateFunc = &Player::UpdateAI;

	// ����������̏�����
	srand(static_cast<unsigned int>(time(nullptr)));

	// �g��̐ݒ�
	Scale = Vec3{ 0.12f,0.12f,0.12f };

	// ���f���̏�������
	InitModel(_manager.GetModelHandle(1));

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

	_oldPos = Position;
}

Player::~Player()
{
}

void Player::Control()
{
	(this->*_controlFunc)();
}

void Player::Update()
{
	(this->*_updateFunc)();
}

void Player::ControlPl()
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::GetInstance();

	// �e�𔭎˂���
	if (input.IsHold(INPUT_X, _padNum) || input.IsHold(INPUT_RIGHT_TRIGGER, _padNum)) {
		BulletTrigger();
	}

	// �N�[���^�C���̌v�Z
	if (_bulletData._bullletCoolTime[NORMAL_BULLET] != 0) {
		_bulletData._bullletCoolTime[NORMAL_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[NORMAL_BULLET] = 0;
	}
	if (_bulletData._bullletCoolTime[GRAPPLER_BULLET] != 0) {
		_bulletData._bullletCoolTime[GRAPPLER_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[GRAPPLER_BULLET] = 0;
	}
	if (_bulletData._bullletCoolTime[BOMB_BULLET] != 0) {
		_bulletData._bullletCoolTime[BOMB_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[BOMB_BULLET] = 0;
	}

	// �e�̎�ނ̂̐؂�ւ�
	if (input.IsTrigger(INPUT_RIGHT_SHOULDER, _padNum)) {

		// �؂�ւ�����炷
		SoundManager::GetInstance().RingSE(SE_BULLET_SELECT);

		if (_bulletData._selectBullet == MAX_TYPE_NUM - 1) {
			_bulletData._selectBullet = MIN_TYPE_NUM;
		}
		else {
			_bulletData._selectBullet++;
		}
	}
	if (input.IsTrigger(INPUT_LEFT_SHOULDER, _padNum)) {

		// �؂�ւ�����炷
		SoundManager::GetInstance().RingSE(SE_BULLET_SELECT);

		if (_bulletData._selectBullet == MIN_TYPE_NUM) {
			_bulletData._selectBullet = MAX_TYPE_NUM - 1;
		}
		else {
			_bulletData._selectBullet--;
		}
	}

	// �E�X�e�B�b�N�ŉ�]
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK, _padNum) > 3000) {

		// �X�e�B�b�N���X���������̉�]�̒l�𑝌�������
		if (input.GetStickVector(INPUT_RIGHT_STICK, _padNum).x != 0) {
			Angle.y += 0.000001f * (input.GetStickThumbX(INPUT_RIGHT_STICK, _padNum));

			// ���W�A���p�𐳋K������
			Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
			if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK, _padNum).z != 0) {
			Angle.z += 0.000001f * (input.GetStickThumbY(INPUT_RIGHT_STICK, _padNum));

			// �ő�l�ƍŒ�l�𒲐�����
			if (Angle.z <= -0.9f) {
				Angle.z = -0.9f;
			}
			else if (Angle.z >= 0.9f) {
				Angle.z = 0.9f;
			}
		}
	}

	// �R���W�����O�̈ړ�

	// �ړ��x�N�g���̏�����
	_moveVec = 0;

	// �X�e�B�b�N�̓��͒l���ړ��x�N�g���ɑ������
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, _padNum) > 3000) {
		_moveVec = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, _padNum);

		// �P�ʃx�N�g���̕����Ɉړ����x���ړ�����x�N�g�����쐬����
		_moveVec = _moveVec * _manager.GetConstantFloat("WALK_SPEED");
	}

	// A�{�^���ŃW�����v
	if (Input::GetInstance().IsTrigger(INPUT_A, _padNum) && _groundFlag) {

		// �W�����v�͂�^����
		_moveScaleY = 2.0f;

		// �W�����v�̊J�n�A�j���[�V�������Đ�
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_JUMP_UP"), false, _manager.GetConstantFloat("BLEND_RATE"));
	}

	// y���̈ړ�������
	_moveVec.y += _moveScaleY;

	// �ړ��x�N�g����y����]������

	// �p�x�̂�����C������
	float angle = Angle.y - 1.5708f;

	// Y����]�s��ɕϊ�
	MATRIX rotaMtx = MGetRotY(angle);

	// �X�e�B�b�N���͂͋t�ɂȂ邩��C������
	_moveVec = Vec3{ _moveVec.x * -1, _moveVec.y, _moveVec.z * -1 };

	// �ړ��x�N�g������]�l�ɍ��킹��Y����]������
	_moveVec = VTransform(_moveVec.VGet(), rotaMtx);

	// �O���b�v���[�̈ړ�
	_moveVec += _grapplerUnitVec * _grapplerScale;

	// ���W�Ɉړ��x�N�g���𑫂�
	Position += _moveVec;

	// �J�v�Z���ɍ��W��n��
	Set(Position);
}

void Player::ControlAI()
{
	// �ړ��x�N�g���̏�����
	_moveVec = 0;

	// �N�[���^�C���̌v�Z
	if (_bulletData._bullletCoolTime[NORMAL_BULLET] != 0) {
		_bulletData._bullletCoolTime[NORMAL_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[NORMAL_BULLET] = 0;
	}
	if (_bulletData._bullletCoolTime[GRAPPLER_BULLET] != 0) {
		_bulletData._bullletCoolTime[GRAPPLER_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[GRAPPLER_BULLET] = 0;
	}
	if (_bulletData._bullletCoolTime[BOMB_BULLET] != 0) {
		_bulletData._bullletCoolTime[BOMB_BULLET]--;
	}
	else {
		_bulletData._bullletCoolTime[BOMB_BULLET] = 0;
	}

	// AI����
	{
		// ��Ƀv���C���[�̕���������
		Vec3 targetPos = _manager.GetPlayerPos();	// �v���C���[�̍��W
		Vec3 length = targetPos - Position;	// �v���C���[�Ƃ̋���
		Vec3 dist = (targetPos - Position).GetNormalized();	// �v���C���[�̕����ւ̒P�ʃx�N�g��
		Angle.y = atan2(dist.x, dist.z) - 1.5708f;	// �v���C���[�̕��������� 

		// forwardVec���v���C���[�̑����̏������������悤�ɂ���
		_forwardVec = (Vec3{targetPos.x,0.0f,targetPos.z} - Position).GetNormalized();

		// �O���b�v�������e���Ă�����v���C���[�̕��@�Ɉړ�����
		if (_bulletManager->IsCollisionBullet(_padNum) && !_bulletManager->GetInvalidFlag(_padNum)) {
			_moveVec += dist * 0.5f;
		}

		// �����_���ȊԊu�ŃW�����v����
		if (rand() % 300 == 0 && _groundFlag) {
			_moveScaleY = 2.0f;
		}

		if (_frame % 60 == 0) {
			if ((Position - _oldPos).Length() < 10.0f) {
				_moveScaleY = 2.0f;
			}
			_oldPos = Position;
		}

		_moveVec += dist * 0.3f;

		// 30�t���[���Ɉ��e�𔭎˂���
		if (_frame % 30 == 0) {
			BulletTrigger();
		}

		// 120�t���[�����Ƃɒe�̎�ނ�؂�ւ���
		if (_frame % 120 == 0) {
			if (_bulletData._bullletCoolTime[GRAPPLER_BULLET] == 0) {
				_bulletData._selectBullet = GRAPPLER_BULLET;
			}
			else if (_bulletData._bullletCoolTime[BOMB_BULLET] == 0) {
				_bulletData._selectBullet = BOMB_BULLET;
			}
			else {
				_bulletData._selectBullet = NORMAL_BULLET;
			}
		}
	}

	// y���̈ړ�������
	_moveVec.y += _moveScaleY;

	// �O���b�v���[�̈ړ�
	_moveVec += _grapplerUnitVec * _grapplerScale;

	// ���W�Ɉړ��x�N�g���𑫂�
	Position += _moveVec;

	// �J�v�Z���ɍ��W��n��
	Set(Position);

}

void Player::UpdatePl()
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

	// �J�����̍X�V
	_pCamera->Update(Position, _forwardVec, Angle);

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

void Player::UpdateAI()
{
	// �t���[���̉��Z
	_frame++;

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

void Player::Draw() const
{

#ifdef _DEBUG
	//DrawCapsule();
	//DrawLine3D(Position.VGet(), (Position + _forwardVec * 20).VGet(), 0x00ffff);
	//DrawFormatString(10, 20, 0xff0000, "x:%f y:%f z:%f angleY:%f angleZ:%f", Position.x, Position.y, Position.z, Angle.y, Angle.z);
	//if (_groundFlag) {
	//	DrawString(10, 40, "OnGrround", 0xff0000);
	//}
	//DrawFormatString(10, 60, 0xff0000, "GrapplerScale:%f", _grapplerScale);
	//if (_selectBullet == NORMAL_BULLET) {
	//	DrawString(10, 80, "NormalBullet", 0xff0000);
	//}
	//else if (_selectBullet == GRAPPLER_BULLET) {
	//	DrawString(10, 80, "GrapplerBullet", 0xff0000);
	//}
	//else if (_selectBullet == BOMB_BULLET) {
	//	DrawString(10, 80, "bombBullet", 0xff0000);
	//}

	//if (_deadFlag) {
	//	DrawString(10, 100, "dead", 0xff0000);
	//}
#endif // DEBUG
	if (_bulletManager->GetBulletExist(_padNum)) {
		DrawLine3D(_bulletManager->GetBulletPos(_padNum).VGet(), Position.VGet(), 0xff16ff);
	}
	// ���f���̕`��
	DrawModel();
}

void Player::CameraSet() const
{
	// �J�����̃^�[�Q�b�g�ƍ��W��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(_pCamera->Position.VGet(), _pCamera->GetTarget().VGet());
}

bool Player::GetGroundFlag() const
{
	return _groundFlag;
}

bool Player::GetDeadFlag() const
{
	return _deadFlag;
}

void Player::KillPlayer()
{
	_deadFlag = true;
}

int Player::GetPlayerNum() const
{
	return _padNum;
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

void Player::BulletTrigger()
{
	// ���˂�����W
	Vec3 pos = MV1GetFramePosition(GetModelHandle(), 65);

	switch (_bulletData._selectBullet)
	{
	case NORMAL_BULLET:
		if (_bulletData._bullletCoolTime[NORMAL_BULLET] == 0) {

			// �ʏ�e���ˉ���炷
			SoundManager::GetInstance().RingSE(SE_SHOT_NORMAL_BULET);

			// �e�𐶐�
			_bulletManager->PushBullet(NORMAL_BULLET, _forwardVec, pos, _padNum);

			// �N�[���^�C����ݒ肷��
			_bulletData._bullletCoolTime[NORMAL_BULLET] = 30;
		}
		break;
	case GRAPPLER_BULLET:
		if (_bulletData._bullletCoolTime[GRAPPLER_BULLET] == 0) {

			// �ʏ�e���ˉ���炷
			SoundManager::GetInstance().RingSE(SE_SHOT_GRAPPLE_BULET);

			// �e�𐶐�
			_bulletManager->PushBullet(GRAPPLER_BULLET, _forwardVec, pos, _padNum);

			// �N�[���^�C����ݒ肷��
			_bulletData._bullletCoolTime[GRAPPLER_BULLET] = 300;
		}
		break;
	case BOMB_BULLET:
		if (_bulletData._bullletCoolTime[BOMB_BULLET] == 0) {

			// �ʏ�e���ˉ���炷
			SoundManager::GetInstance().RingSE(SE_SHOT_BOMB_BULET);

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

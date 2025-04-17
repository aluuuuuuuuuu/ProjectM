#include "BombBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Application.h"

BombBullet::BombBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr),
	_frame(0)
{
	// �����ʒu�̐ݒ�
	Position = pos;

	// �o���b�g�^�C�v�̐ݒ�
	_bulletType = BOMB_BULLET;

	// ���˂����v���C���[�̕ۑ�
	_playerNum = plNum;

	// �i�ޕ���
	_distVec = dist;

	// �G�t�F�N�g�C���X�^���X�̍쐬
	_pEffect = std::make_shared<MyEffect>(BOMB_BULLET_EFFECT, pos);

	// ���a�̐ݒ�
	_radius = _bulletManager.GetConstantFloat("RADIUS");
}

BombBullet::~BombBullet()
{
	if (_frame == 0) {
		_pEffect->StopEffect();
	}
	else if (!_deadFlag) {
		_explosionEffect->StopEffect();
	}
}

void BombBullet::Update()
{
	if (!_collisionFlag && _frame == 0) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED") * 0.5f;
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	// ���̃��C�����z������폜����
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	if (_frame > 0) {
		_explosionEffect->Update(Position);
		_frame++;
		if (_frame == Application::GetInstance().GetConstantInt("FRAME_NUM")) {
			_deadFlag = true;
			_explosionEffect->StopEffect();
		}
	}
	else {
		// �}�b�v�Ƃ̓����蔻����Ƃ�
		if (_collManager->CollisionBullet(Position, _radius, BOMB_BULLET)) {

			SoundManager::GetInstance().RingSE(SE_EXPLOSION);

			_pEffect->StopEffect();
			_explosionEffect = std::make_shared<MyEffect>(BLOCK_DESTROY_EFFECT, Position);
			_frame = 1;
		}
	}

	// �G�t�F�N�g�̍X�V
	_pEffect->Update(Position);
}

void BombBullet::Draw() const
{
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0xf0ff00, 0xf0ff00, true);
}

void BombBullet::PlayerCollision()
{
}

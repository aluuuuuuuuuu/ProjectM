#include "GrapplerBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "WedgewormManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundManager.h"

GrapplerBullet::GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum, std::shared_ptr<WedgewormManager>& wedge) :
	_collManager(col),
	_bulletManager(mgr),
	_frame(0),
	_wedgeManager(wedge)

{
	// �����ʒu�̐ݒ�
	Position = pos;

	// �o���b�g�^�C�v�̐ݒ�
	_bulletType = GRAPPLER_BULLET;

	// ���˂����v���C���[�̕ۑ�
	_playerNum = plNum;

	// �i�ޕ���
	_distVec = dist;

	// �G�t�F�N�g�C���X�^���X�̍쐬
	_pEffect = std::make_shared<MyEffect>(GRAPPLE_BULLET_EFFECT, pos);
}

GrapplerBullet::~GrapplerBullet()
{
	if (!_deadFlag) {
		_pEffect->StopEffect();
	}
}

void GrapplerBullet::Update()
{
	if (!_collisionFlag) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED");
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;
	}

	// ���̃��C�����z������폜����
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	// �}�b�v�Ƃ̓����蔻����Ƃ�
	if (_collManager->CollisionBullet(Position, 3.0f, GRAPPLER_BULLET)) {

		_collisionFlag = true;
	}
	//// �S���Ƃ̓����蔻����Ƃ�
	//for (int i = 0; i < 2; i++) {
	//	Vec3 pos = _wedgeManager->GetPos(i);
	//	float dist = (pos - Position).Length();

	//	if (dist < 16.0f + 16.0f) {
	//		_collisionFlag = true;
	//	}
	//}

	// �������Ă���莞�Ԏc��悤�ɂ���
	if (_invalidFlag) {
		_frame++;
		if (_frame >= 80) {
			_deadFlag = true;
		}
	}
	
	// �G�t�F�N�g�̍폜
	if (_deadFlag) {
		_pEffect->StopEffect();
	}

	// �G�t�F�N�g�̍X�V
	_pEffect->Update(Position);
}

void GrapplerBullet::Draw() const
{
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0xff00ff, 0xff00ff, true);
}

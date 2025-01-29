#include "NormalBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"

NormalBullet::NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr)
{
	// �����ʒu�̐ݒ�
	Position = pos;

	// �o���b�g�^�C�v�̐ݒ�
	_bulletType = NORMAL_BULLET;

	// ���˂����v���C���[�̕ۑ�
	_playerNum = plNum;

	// �i�ޕ���
	_distVec = dist;

	// �G�t�F�N�g�C���X�^���X�̍쐬
	_pEffect = std::make_shared<MyEffect>(NORMAL_BULLET_EFFECT,pos);
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Update()
{
	// �|�W�V�����̍X�V
	Position += _distVec *  _bulletManager.GetConstantFloat("SPEED");

	// �d�͂̉e����^����
	_gravity += _bulletManager.GetConstantFloat("GRAVITY");
	Position.y -= _gravity;

	// ���̃��C�����z������폜����
	float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
	if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
		_deadFlag = true;
	}

	// �}�b�v�Ƃ̓����蔻����Ƃ�
	if (_collManager->CollisionBullet(Position, 3.0f,NORMAL_BULLET)) _deadFlag = true;

	if (_deadFlag) {
		_pEffect->StopEffect();
	}

	_pEffect->Update(Position);
}

void NormalBullet::Draw() const
{
#ifdef _DEBUG
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0x0000ff, 0x0000ff, true);
#endif // DEBUG
}

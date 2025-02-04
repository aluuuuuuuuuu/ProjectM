#include "NormalBullet.h"
#include "MapBulletCollisionManager.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "SoundManager.h"

NormalBullet::NormalBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum) :
	_collManager(col),
	_bulletManager(mgr),
	_frame(0)
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
	if (_frame == 0) {
		_pEffect->StopEffect();
	}
	else if (!_deadFlag){
		_destroyEffect->StopEffect();
	}
}

void NormalBullet::Update()
{
	// �|�W�V�����̍X�V
	if (_frame == 0) {
		Position += _distVec * _bulletManager.GetConstantFloat("SPEED");
		// �d�͂̉e����^����
		_gravity += _bulletManager.GetConstantFloat("GRAVITY");
		Position.y -= _gravity;

		// �}�b�v�Ƃ̓����蔻����Ƃ�
		if (_collManager->CollisionBullet(Position, 3.0f, NORMAL_BULLET)) {

			// ���e����炷
			SoundManager::GetInstance().RingSE(SE_DESTRUCTION);

			_frame = 1;
			_pEffect->StopEffect();
			_destroyEffect = std::make_shared<MyEffect>(BLOCK_DESTROY_EFFECT, Position);
			_destroyEffect->SetScaleEffect(Vec3{ 0.1f,0.1f,0.1f });
		}

		// ���̃��C�����z������폜����
		float deadLine = _bulletManager.GetConstantFloat("DEAD_LINE");
		if (abs(Position.x) >= deadLine || abs(Position.y) >= deadLine || abs(Position.z) >= deadLine) {
			_deadFlag = true;
			_pEffect->StopEffect();
		}
	}
	else {
		_destroyEffect->Update(Position);
		_frame++;
		if (_frame > 60) {
			_deadFlag = true;
			_destroyEffect->StopEffect();
		}
	}

	// �G�t�F�N�g�̍X�V
	_pEffect->Update(Position);
}

void NormalBullet::Draw() const
{
#ifdef _DEBUG
	//DrawSphere3D(Position.VGet(), 3.0f, 16, 0x0000ff, 0x0000ff, true);
#endif // DEBUG
}

#include "BulletManager.h"
#include "NormalBullet.h"
#include "Vec3.h"
#include "MapBulletCollisionManager.h"
#include "GrapplerBullet.h"

BulletManager::BulletManager(std::shared_ptr<MapBulletCollisionManager>& col):
	_collManager(col)
{
	// �萔�̓ǂݍ���
	ReadCSV("data/constant/NormalBullet.csv");
}

BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
	// �o���b�g�̍X�V
	for (auto& bullet : _pBullet) {
		bullet->Update();
	}

	// �o���b�g������ł�����폜����
	for (auto it = _pBullet.begin(); it != _pBullet.end();) {
		if ((*it)->IsDead()) {
			it = _pBullet.erase(it);	//�v�f���폜�����̗v�f���w���C�e���[�^���擾
		}
		else {
			it++;
		}
	}
}

void BulletManager::Draw() const
{
	for (auto& bullet : _pBullet) {
		bullet->Draw();
	}
}

void BulletManager::PushBullet(int bul, Vec3 dist, Vec3 pos)
{
	switch (bul)
	{
	case NORMAL_BULLET:
		_pBullet.push_back(std::make_shared<NormalBullet>(dist, pos,_collManager,*this));
		break;
	case GRAPPLER_BULLET:
		_pBullet.push_back(std::make_shared<GrapplerBullet>(dist, pos, _collManager, *this));
	default:
		break;
	}
}

bool BulletManager::IsCollisionBullet()
{

	for (auto& bullet : _pBullet) {
		if (bullet->GetBulletType() == GRAPPLER_BULLET) {
			if (bullet->GetCollisionFlag()) {
				return true;
			}
		}
	}

	return false;
}


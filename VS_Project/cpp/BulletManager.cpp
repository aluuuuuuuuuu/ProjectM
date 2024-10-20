#include "BulletManager.h"
#include "NormalBullet.h"
#include "Vec3.h"

BulletManager::BulletManager()
{
	_pBullet.push_back(std::make_shared<NormalBullet>(Vec3(), Vec3()));
}

BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
	for (auto& bullet : _pBullet) {
		bullet->Update();
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
		_pBullet.push_back(std::make_shared<NormalBullet>(dist, pos));
		break;
	default:
		break;
	}
}


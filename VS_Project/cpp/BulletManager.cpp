#include "BulletManager.h"
#include "NormalBullet.h"
#include "Vec3.h"
#include "MapBulletCollisionManager.h"

BulletManager::BulletManager(std::shared_ptr<MapBulletCollisionManager>& col):
	_collManager(col)
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
	// バレットの更新
	for (auto& bullet : _pBullet) {
		bullet->Update();
	}

	// バレットが死んでいたら削除する
	for (auto it = _pBullet.begin(); it != _pBullet.end();) {
		if ((*it)->IsDead()) {
			it = _pBullet.erase(it);	//要素を削除し次の要素を指すイテレータを取得
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
		_pBullet.push_back(std::make_shared<NormalBullet>(dist, pos,_collManager));
		break;
	default:
		break;
	}
}


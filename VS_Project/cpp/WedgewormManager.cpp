#include "WedgewormManager.h"
#include "Wedgeworm.h"

WedgewormManager::WedgewormManager()
{
	// wormオブジェクトの初期化
	int num = 0;
	for (auto& obj : _worm) {
		obj = std::make_shared<Wedgeworm>(num);
		num++;
	}
}

WedgewormManager::~WedgewormManager()
{
}

void WedgewormManager::Update()
{
	// wormの更新処理
	for (auto& obj : _worm) {
		obj->Update();
	}
}

void WedgewormManager::Draw() const
{
	// wormの描画処理
	for (auto& obj : _worm) {
		obj->Draw();
	}
}

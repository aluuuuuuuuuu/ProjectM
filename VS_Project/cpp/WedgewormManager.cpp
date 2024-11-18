#include "WedgewormManager.h"
#include "Wedgeworm.h"

WedgewormManager::WedgewormManager()
{
	// worm�I�u�W�F�N�g�̏�����
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
	// worm�̍X�V����
	for (auto& obj : _worm) {
		obj->Update();
	}
}

void WedgewormManager::Draw() const
{
	// worm�̕`�揈��
	for (auto& obj : _worm) {
		obj->Draw();
	}
}

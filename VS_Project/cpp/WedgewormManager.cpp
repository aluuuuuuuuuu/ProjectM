#include "WedgewormManager.h"
#include "Wedgeworm.h"

WedgewormManager::WedgewormManager()
{
	// ���f���̃��[�h
	int modelHandle = MV1LoadModel("data/model/Wedgeworm.mv1");

	// worm�I�u�W�F�N�g�̏�����
	int num = 0;
	for (auto& obj : _worm) {
		obj = std::make_shared<Wedgeworm>(num, modelHandle);
		num++;
	}

	MV1DeleteModel(modelHandle);
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

Vec3 WedgewormManager::GetPos(int num) const
{
	return _worm[num]->Position;
}

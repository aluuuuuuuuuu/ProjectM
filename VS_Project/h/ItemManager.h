#pragma once
#include <memory>
#include <vector>
#include "Vec3.h"
#include "Constant.h"

namespace {
	constexpr int ITEM_TYPE_SPEED = 0;
}

class StageManager;
class ItemBase;
class PlayerManager;
class ItemManager:
	public Constant
{
public:

	
	ItemManager(std::shared_ptr<PlayerManager>& playerManager,std::shared_ptr<StageManager>& stageManager);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ItemManager();

	void Update();

	void Draw() const;


private:

	/// <summary>
	/// �v���C���[�ƃA�C�e���̓����蔻����Ƃ�
	/// </summary>
	void Collision();

	Vec3 ClosestPointLine(Vec3 itemPos, Vec3 capsuleA, Vec3 capsuleB);

	float DistanceClosestPoint(Vec3 closest, Vec3 itemPos);


	std::vector<std::shared_ptr<ItemBase>> _pItem;

	// �t���[���J�E���^
	int _frame;

	std::shared_ptr<PlayerManager>& _pPlayer;

	std::shared_ptr<StageManager>& _pStage;
};


#include "ItemSpeedUp.h"
#include "DxLib.h"
#include "ItemManager.h"
#include "StageManager.h"

ItemSpeedUp::ItemSpeedUp(Vec3 pos, std::shared_ptr<StageManager>& stageManager):
	_pStage(stageManager)
{
	// 初期位置の設定
	Position = pos;
	Scale = 17.0f;

	_moveVec.y = -0.5f;

	// アイテムタイプの設定
	_itemType = ITEM_TYPE_SPEED;

	// モデルの設定
	InitModel(MV1LoadModel("data/model/pumpkin.mv1"));	
}

ItemSpeedUp::~ItemSpeedUp()
{
}

void ItemSpeedUp::Update()
{
	if (_invalidFlag) {
		_frame++;
		if (_frame > 10) {
			_deadFlag = true;
		}
	}
	else {
		Position += _moveVec;

		int x = static_cast<int>( Position.x / 10.0f) + 1;
		int z = static_cast<int>( Position.z / 10.0f) + 1;

		if (_pStage->GetStageInfo(x, 1, z) != 0) {
			if (Position.y < 13.0f) {
				Position.y = 13.0f;
			}

			if (Position.y == 13.0f) {
				_frame++;

				if (_frame > 180) {
					_invalidFlag = true;
					_frame = 0;
				}
			}
		}
		else if (_pStage->GetStageInfo(x, 0, z) != 0) {
			if (Position.y < 2.0f) {
				Position.y = 2.0f;
			}

			if (Position.y == 2.0f) {
				_frame++;

				if (_frame > 180) {
					_invalidFlag = true;
					_frame = 0;
				}
			}
		}
		else {
			if (Position.y < 100) {
				_deadFlag = true;
			}
		}
	}
	UpdateModel(GetTransformInstance());
}

void ItemSpeedUp::Draw() const
{
	DrawModel();
}

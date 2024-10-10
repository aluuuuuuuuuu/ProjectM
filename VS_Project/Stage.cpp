#include "Stage.h"
#include "DxLib.h"

constexpr int kBlockSize = 10;

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::DrawStage() const
{
	for (int i = 0; i < 10; i++) 
	{
		for (int n = 0; n < 2; n++) 
		{
			for (int k = 0; k < 10; k++) 
			{
				VECTOR pos = { i * 10 - kBlockSize * 5 , n * 10 , k * 10 - kBlockSize * 5 };
				DrawSphere3D(pos, 5.0f, 8, 0xff0000, 0xff0000, true);
			}
		}
	}
}

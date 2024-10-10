#include "StageManager.h"
#include "DxLib.h"

constexpr int kBlockSize = 10;

StageManager::StageManager()
{
	// すべての要素に1を代入するための3重ループ
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 10; ++k) {
				_stage[i][j][k] = 1;
			}
		}
	}

	_stage[0][1][0] = 0;
	_stage[4][1][2] = 0;
}

StageManager::~StageManager()
{
}

void StageManager::DrawStage() const
{
	for (int i = 0; i < 10; i++) 
	{
		for (int n = 0; n < 2; n++) 
		{
			for (int k = 0; k < 10; k++) 
			{
				if (_stage[i][n][k] != 0) {
					VECTOR pos = { i * 10  , n * 10 , k * 10};
					DrawSphere3D(VECTOR{ pos.x - 5,pos.y - 5 ,pos.z - 5 }, 5.0f, 8, 0xff0000, 0xff0000, true);
				}
			}
		}
	}
}

int StageManager::GetStageInfo(int a, int b, int c)
{
	return _stage[a][b][c];
}

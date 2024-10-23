#include "StageManager.h"
#include "DxLib.h"


StageManager::StageManager() :
	_size(0),
	_modelHandle(0)
{
	// 定数のロード
	ReadCSV("data/constant/Stage.csv");

	_size = GetConstantInt("BLOCK_SIZE");

	// モデルのロード
	_modelHandle = MV1LoadModel("data/model/tileMedium_forest.mv1");

	// ステージの初期化
	for (int i = 0; i < BLOCK_NUM_X; ++i) {
		for (int j = 0; j < BLOCK_NUM_Y; ++j) {
			for (int k = 0; k < BLOCK_NUM_Z; ++k) {

				// すべての要素に１を入れる
				_stage[i][j][k] = 1;

				// モデルを複製する
				_model[i][j][k] = MV1DuplicateModel(_modelHandle);

				// 拡大率の設定
				MV1SetScale(_model[i][j][k], VGet(GetConstantFloat("BLOCK_SCALE_X"),
												  GetConstantFloat("BLOCK_SCALE_Y"),
												  GetConstantFloat("BLOCK_SCALE_Z")));

				// 座標の設定
				VECTOR pos = { static_cast<float>(i * GetConstantInt("BLOCK_SIZE")),
							   static_cast<float>(j * GetConstantInt("BLOCK_SIZE")),
							   static_cast<float>(k * GetConstantInt("BLOCK_SIZE")) };
				MV1SetPosition(_model[i][j][k], VECTOR{ pos.x - GetConstantFloat("BLOCK_MARGIN_X"),
														pos.y - GetConstantFloat("BLOCK_MARGIN_Y") ,
														pos.z - GetConstantFloat("BLOCK_MARGIN_Z") });
			}
		}
	}

	_stage[0][1][1] = 0;
	_stage[0][1][2] = 0;
	_stage[0][1][3] = 0;
	_stage[0][1][4] = 0;
	_stage[1][1][1] = 0;
	_stage[1][1][2] = 0;
	_stage[1][1][3] = 0;
	_stage[1][1][4] = 0;
	_stage[0][1][5] = 0;
	_stage[0][1][6] = 0;
	_stage[0][1][7] = 0;
	_stage[0][1][8] = 0;
	_stage[1][1][5] = 0;
	_stage[1][1][6] = 0;
	_stage[1][1][7] = 0;
	_stage[1][1][8] = 0;



	_stage[6][1][0] = 0;
	_stage[4][1][2] = 0;
}

StageManager::~StageManager()
{
}

void StageManager::DrawStage() const
{
	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		for (int n = 0; n < BLOCK_NUM_Y; n++)
		{
			for (int k = 0; k < BLOCK_NUM_Z; k++)
			{
				if (_stage[i][n][k] != 0) {

					MV1DrawModel(_model[i][n][k]);
				}
			}
		}
	}
}

int StageManager::GetStageInfo(int a, int b, int c)
{
	return _stage[a][b][c];
}

void StageManager::DeleteBox(int x, int y, int z)
{
	_stage[x][y][z] = 0;
}

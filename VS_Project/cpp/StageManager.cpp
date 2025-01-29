#include "StageManager.h"
#include "DxLib.h"


StageManager::StageManager() :
	_size(0),
	_modelHandleGreen(0)
{
	// �萔�̃��[�h
	ReadCSV("data/constant/Stage.csv");

	_size = GetConstantInt("BLOCK_SIZE");

	// ���f���̃��[�h
	_modelHandleGreen = MV1LoadModel("data/model/tileMedium_forest.mv1");
	_modelHandleRed = MV1LoadModel("data/model/tileMedium_Red.mv1");

	// �X�e�[�W�̏�����
	for (int i = 0; i < BLOCK_NUM_X; ++i) {
		for (int j = 0; j < BLOCK_NUM_Y; ++j) {
			for (int k = 0; k < BLOCK_NUM_Z; ++k) {

				// ���ׂĂ̗v�f�ɂP������
				_stage[i][j][k] = 1;

				// ���f���𕡐�����
				if (j == 1) {
					_model[i][j][k] = MV1DuplicateModel(_modelHandleGreen);
				}
				else {
					_model[i][j][k] = MV1DuplicateModel(_modelHandleRed);
				}

				// �g�嗦�̐ݒ�
				MV1SetScale(_model[i][j][k], VGet(GetConstantFloat("BLOCK_SCALE_X"),
												  GetConstantFloat("BLOCK_SCALE_Y"),
												  GetConstantFloat("BLOCK_SCALE_Z")));

				// ���W�̐ݒ�
				VECTOR pos = { static_cast<float>(i * GetConstantInt("BLOCK_SIZE")),
							   static_cast<float>(j * GetConstantInt("BLOCK_SIZE")),
							   static_cast<float>(k * GetConstantInt("BLOCK_SIZE")) };
				MV1SetPosition(_model[i][j][k], VECTOR{ pos.x - GetConstantFloat("BLOCK_MARGIN_X"),
														pos.y - GetConstantFloat("BLOCK_MARGIN_Y") ,
														pos.z - GetConstantFloat("BLOCK_MARGIN_Z") });
			}
		}
	}
}

StageManager::~StageManager()
{
	MV1DeleteModel(_modelHandleGreen);
	MV1DeleteModel(_modelHandleRed);
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
	// �͈͊O�������ꍇ�͉������Ȃ�
	if (x < 0 || x >= BLOCK_NUM_X ||
		y < 0 || y >= BLOCK_NUM_Y ||
		z < 0 || z >= BLOCK_NUM_Z) {
		return;
	}

	_stage[x][y][z] = 0;
}

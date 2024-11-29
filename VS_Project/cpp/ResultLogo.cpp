#include "ResultLogo.h"
#include "DxLib.h"

ResultLogo::ResultLogo()
{
	_logoHandle = LoadGraph("data/image/Winner.png");
}

ResultLogo::~ResultLogo()
{
	DeleteGraph(_logoHandle);
}

void ResultLogo::Draw() const
{

	// �������S�̕`��
	DrawGraph(144, 568, _logoHandle, true);
}

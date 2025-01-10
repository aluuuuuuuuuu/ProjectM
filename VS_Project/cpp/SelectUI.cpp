#include "SelectUI.h"
#include "DxLib.h"

SelectUI::SelectUI()
{
	// ���͉摜�̃��[�h
	_selectFighterHandle = LoadGraph("data/image/SelectFighter.png");

	// �߂�摜�̃��[�h
	_returnHandle = LoadGraph("data/image/return.png");
}

SelectUI::~SelectUI()
{
}

void SelectUI::Update()
{
}

void SelectUI::Draw() const
{
	// �߂�摜�̕`��
	DrawGraph(0, 0, _returnHandle, true);

	// ���͂̕`��
	DrawRotaGraph(960, 190, 1, 0, _selectFighterHandle, true);
}

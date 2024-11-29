#include "ResultUi.h"
#include "DxLib.h"

ResultUi::ResultUi()
{
	// �e�摜�̃��[�h
	_resultLogoHandle = LoadGraph("data/image/Winner.png");
	_redLineHandle = LoadGraph("data/image/RedLine.png");
	_timeStringHandle = LoadGraph("data/image/TimeString.png");
	_rankFrame = LoadGraph("data/image/RankFrame.png");
	_rankHandle = LoadGraph("data/image/RankS.png");

}

ResultUi::~ResultUi()
{
	// �摜�̃f���[�g
	DeleteGraph(_resultLogoHandle);
	DeleteGraph(_redLineHandle);
	DeleteGraph(_timeStringHandle);
	DeleteGraph(_rankFrame);
	DeleteGraph(_rankHandle);

}

void ResultUi::Update()
{
}

void ResultUi::Draw() const
{
	// �Ԑ��̕`��
	DrawGraph(0, 430, _redLineHandle, true);

	// ���U���g���S�̕`��
	DrawGraph(144, 568, _resultLogoHandle, true);
	
	// �����N�g�̕`��
	DrawGraph(1045, 430, _rankFrame, true);

	// ���j�^�C��������̕`��
	DrawGraph(62, 156, _timeStringHandle, true);

	// �����N�����̉摜�̕`��
	DrawGraph(1459, 537, _rankHandle, true);

	// ��ʘg�̕`��
	// ���̘g��
	DrawBox(0, 1000, 1920, 1080, 0x000000, true);

	// ��̘g��
	DrawBox(0, 0, 1920, 80, 0x000000, true);

}

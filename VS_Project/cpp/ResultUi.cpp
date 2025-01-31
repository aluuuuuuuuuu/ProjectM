#include "ResultUi.h"
#include "DxLib.h"

ResultUi::ResultUi(int time)
{
	// �e�摜�̃��[�h
	_resultLogoHandle = LoadGraph("data/image/Winner.png");
	_redLineHandle = LoadGraph("data/image/RedLine.png");
	_timeStringHandle = LoadGraph("data/image/TimeString.png");
	_rankFrame = LoadGraph("data/image/RankFrame.png");
	_guide = LoadGraph("data/image/Guide.png");

	// ���Ԃɂ���ă��[�h����摜��ύX����
	if (time <= 1800) {
		_rankHandle = LoadGraph("data/image/RankS.png");	// S�����N
	}
	else if (time <= 3600) {
		_rankHandle = LoadGraph("data/image/RankA.png");	// A�����N
	}
	else if(time <= 7200) {
		_rankHandle = LoadGraph("data/image/RankB.png");	// B�����N
	}
	else {
		_rankHandle = LoadGraph("data/image/RankC.png");	// C�����N
	}

}

ResultUi::~ResultUi()
{
	// �摜�̃f���[�g
	DeleteGraph(_resultLogoHandle);
	DeleteGraph(_redLineHandle);
	DeleteGraph(_timeStringHandle);
	DeleteGraph(_rankFrame);
	DeleteGraph(_rankHandle);
	DeleteGraph(_guide);
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
	DrawBox(0, 990, 1920, 1080, 0x000000, true);

	// ��̘g��
	DrawBox(0, 0, 1920, 90, 0x000000, true);
	
	// �{�^�������̕`��
	DrawGraph(900, 990, _guide, true);
}

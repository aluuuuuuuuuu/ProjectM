#include "ResultUi.h"
#include "DxLib.h"

ResultUi::ResultUi()
{
	// Še‰æ‘œ‚Ìƒ[ƒh
	_resultLogoHandle = LoadGraph("data/image/Winner.png");
	_redLineHandle = LoadGraph("data/image/RedLine.png");
	_timeStringHandle = LoadGraph("data/image/TimeString.png");
	_rankFrame = LoadGraph("data/image/RankFrame.png");
	_rankHandle = LoadGraph("data/image/RankS.png");

}

ResultUi::~ResultUi()
{
	// ‰æ‘œ‚ÌƒfƒŠ[ƒg
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
	// Ôü‚Ì•`‰æ
	DrawGraph(0, 430, _redLineHandle, true);

	// ƒŠƒUƒ‹ƒgƒƒS‚Ì•`‰æ
	DrawGraph(144, 568, _resultLogoHandle, true);
	
	// ƒ‰ƒ“ƒN˜g‚Ì•`‰æ
	DrawGraph(1045, 430, _rankFrame, true);

	// Œ‚”jƒ^ƒCƒ€•¶š—ñ‚Ì•`‰æ
	DrawGraph(62, 156, _timeStringHandle, true);

	// ƒ‰ƒ“ƒN•¶š‚Ì‰æ‘œ‚Ì•`‰æ
	DrawGraph(1459, 537, _rankHandle, true);

	// ‰æ–Ê˜g‚Ì•`‰æ
	// ‰º‚Ì˜gü
	DrawBox(0, 1000, 1920, 1080, 0x000000, true);

	// ã‚Ì˜gü
	DrawBox(0, 0, 1920, 80, 0x000000, true);

}

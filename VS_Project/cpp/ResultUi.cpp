#include "ResultUi.h"
#include "DxLib.h"

ResultUi::ResultUi(int time)
{
	// 各画像のロード
	_resultLogoHandle = LoadGraph("data/image/Winner.png");
	_redLineHandle = LoadGraph("data/image/RedLine.png");
	_timeStringHandle = LoadGraph("data/image/TimeString.png");
	_rankFrame = LoadGraph("data/image/RankFrame.png");

	// 時間によってロードする画像を変更する
	if (time <= 100) {
		_rankHandle = LoadGraph("data/image/RankS.png");	// Sランク
	}
	else if (time <= 200) {
		_rankHandle = LoadGraph("data/image/RankA.png");	// Aランク
	}
	else if(time <= 300) {
		_rankHandle = LoadGraph("data/image/RankB.png");	// Bランク
	}
	else {
		_rankHandle = LoadGraph("data/image/RankC.png");	// Cランク
	}

}

ResultUi::~ResultUi()
{
	// 画像のデリート
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
	// 赤線の描画
	DrawGraph(0, 430, _redLineHandle, true);

	// リザルトロゴの描画
	DrawGraph(144, 568, _resultLogoHandle, true);
	
	// ランク枠の描画
	DrawGraph(1045, 430, _rankFrame, true);

	// 撃破タイム文字列の描画
	DrawGraph(62, 156, _timeStringHandle, true);

	// ランク文字の画像の描画
	DrawGraph(1459, 537, _rankHandle, true);

	// 画面枠の描画
	// 下の枠線
	DrawBox(0, 1000, 1920, 1080, 0x000000, true);

	// 上の枠線
	DrawBox(0, 0, 1920, 80, 0x000000, true);

}

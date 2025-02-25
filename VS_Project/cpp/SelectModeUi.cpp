#include "SelectModeUi.h"
#include "DxLib.h"

SelectModeUi::SelectModeUi() :
	_selectButtonNum(SOLO_MODE),
	_circleAngle(0.0)
{
	// 画像のロード
	_circleHandle = LoadGraph("data/image/CenterCircle.png");

	_buttonHandle[SOLO_MODE] = LoadGraph("data/image/Button1.png");
	_buttonHandle[MULTI_MODE] = LoadGraph("data/image/Button2.png");
	_buttonHandle[TUTORIAL_MODE] = LoadGraph("data/image/Button3.png");
	_buttonHandle[OPTION_MODE] = LoadGraph("data/image/Button4.png");

	_messageHandle[SOLO_MODE] = LoadGraph("data/image/Message01.png");
	_messageHandle[MULTI_MODE] = LoadGraph("data/image/Message02.png");
	_messageHandle[TUTORIAL_MODE] = LoadGraph("data/image/Message03.png");
	_messageHandle[OPTION_MODE] = LoadGraph("data/image/Message04.png");

	for (auto& scale : _buttonScale) {
		scale = 1.0;
	}

	// 中央の円の座標
	_circlePos = Vec2{ 960,540 };
}

SelectModeUi::~SelectModeUi()
{
	// 画像の削除
	DeleteGraph(_circleHandle);
	for (auto& handle : _buttonHandle) {
		DeleteGraph(handle);
	}
}

void SelectModeUi::Update()
{
}

void SelectModeUi::Draw() const
{
	// ボタンの描画
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(_buttonPos[i].intX(), _buttonPos[i].intY(), _buttonScale[i], 0.0, _buttonHandle[i], true);
	}

	// 中央の円の描画
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), 1.0, 0.0, _circleHandle, true);

	// 下のメッセージハンドル
	DrawRotaGraph(960, 1033, 1.0, 0.0, _messageHandle[_selectButtonNum], true);

	// 下の四角の描画
	DrawBox(0, 986, 1920, 1080, 0x000000, true);
}

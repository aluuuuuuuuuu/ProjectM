#include "NumSelectButton.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerManager.h"

NumSelectButton::NumSelectButton():
	_selectNum(1)
{
	// 人数選択の画像のロード
	_numHandle[PLAYER_ONE] = LoadGraph("data/image/1play.png");
	_numHandle[PLAYER_TWO] = LoadGraph("data/image/2play.png");
	_numHandle[PLAYER_THREE] = LoadGraph("data/image/3play.png");
	_numHandle[PLAYER_FORE] = LoadGraph("data/image/4play.png");

	// 選択矢印のロード
	_arrowHandle = LoadGraph("data/image/arrow.png");

	// ゲーム終了画像のロード
	_gameEndHandle = LoadGraph("");

	_arrowPos = Vec2{ 690,875 };
}

NumSelectButton::~NumSelectButton()
{
	// 画像の削除
	for (auto& han : _numHandle) {
		DeleteGraph(han);
	}

	DeleteGraph(_gameEndHandle);

}

void NumSelectButton::Update()
{
	auto& input = Input::GetInstance();

	if (input.IsTrigger(INPUT_RIGHT, INPUT_PAD_1)) {
		switch (_arrowPos.intX())
		{
		case 690:
			_arrowPos.x = static_cast<int>(890);
			_selectNum = PLAYER_TWO;
			break;
		case 890:
			_arrowPos.x = static_cast<int>(1090);
			_selectNum = PLAYER_THREE;
			break;
		case 1090:
			_arrowPos.x = static_cast<int>(1290);
			_selectNum = PLAYER_FORE;
			break;
		case 1290:
			_arrowPos.x = static_cast<int>(690);
			_selectNum = PLAYER_ONE;
			break;
		default:
			break;
		}
	}
	if (input.IsTrigger(INPUT_LEFT, INPUT_PAD_1)) {
		switch (_arrowPos.intX())
		{
		case 690:
			_arrowPos.x = static_cast<int>(1290);
			_selectNum = PLAYER_FORE;
			break;
		case 890:
			_arrowPos.x = static_cast<int>(690);
			_selectNum = PLAYER_ONE;
			break;
		case 1090:
			_arrowPos.x = static_cast<int>(890);
			_selectNum = PLAYER_TWO;
			break;
		case 1290:
			_arrowPos.x = static_cast<int>(1090);
			_selectNum = PLAYER_THREE;
			break;
		default:
			break;
		}
	}
}

void NumSelectButton::Draw() const
{
	// 矢印の描画
	DrawRotaGraph(_arrowPos.intX(), _arrowPos.intY(), 1, 0, _arrowHandle, true);

	// 人数の描画
	DrawRotaGraph(690, 950, 1, 0, _numHandle[0], true);
	DrawRotaGraph(890, 950, 1, 0, _numHandle[1], true);
	DrawRotaGraph(1090, 950, 1, 0, _numHandle[2], true);
	DrawRotaGraph(1290, 950, 1, 0, _numHandle[3], true);
}

int NumSelectButton::GetSelectNum() const
{
	return _selectNum;
}

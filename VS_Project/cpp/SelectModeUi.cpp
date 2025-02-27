#include "SelectModeUi.h"
#include "DxLib.h"
#include "Input.h"
#include "MyMath.h"
#include "Vec3.h"
#include "SoundManager.h"

SelectModeUi::SelectModeUi() :
	_selectButtonNum(SOLO_MODE),
	_circleAngle(0.0),
	_frame(0),
	_input(false),
	_circleScale(1.0),
	_changeFrag(false)
{
	// 画像のロード
	{
		// 中央の円
		_circleHandle[SOLO_MODE] = LoadGraph("data/image/CenterCircle1.png");
		_circleHandle[MULTI_MODE] = LoadGraph("data/image/CenterCircle2.png");
		_circleHandle[TUTORIAL_MODE] = LoadGraph("data/image/CenterCircle3.png");
		_circleHandle[OPTION_MODE] = LoadGraph("data/image/CenterCircle4.png");

		_circleLogoHandle = LoadGraph("data/image/CenterCircleLogo.png");

		_centerArrowHandle[SOLO_MODE] = LoadGraph("data/image/CenterArrow1.png");
		_centerArrowHandle[MULTI_MODE] = LoadGraph("data/image/CenterArrow2.png");
		_centerArrowHandle[TUTORIAL_MODE] = LoadGraph("data/image/CenterArrow3.png");
		_centerArrowHandle[OPTION_MODE] = LoadGraph("data/image/CenterArrow4.png");

		// ボタン
		_buttonHandle[SOLO_MODE] = LoadGraph("data/image/Button1.png");
		_buttonHandle[MULTI_MODE] = LoadGraph("data/image/Button2.png");
		_buttonHandle[TUTORIAL_MODE] = LoadGraph("data/image/Button3.png");
		_buttonHandle[OPTION_MODE] = LoadGraph("data/image/Button4.png");

		// ハイライト
		_highlightHandle[SOLO_MODE] = LoadGraph("data/image/Highlight1.png");
		_highlightHandle[MULTI_MODE] = LoadGraph("data/image/Highlight2.png");
		_highlightHandle[TUTORIAL_MODE] = LoadGraph("data/image/Highlight3.png");
		_highlightHandle[OPTION_MODE] = LoadGraph("data/image/Highlight4.png");

		// メッセージ
		_messageHandle[SOLO_MODE] = LoadGraph("data/image/Message01.png");
		_messageHandle[MULTI_MODE] = LoadGraph("data/image/Message02.png");
		_messageHandle[TUTORIAL_MODE] = LoadGraph("data/image/Message03.png");
		_messageHandle[OPTION_MODE] = LoadGraph("data/image/Message04.png");

		// 余白
		_marginHandle[SOLO_MODE] = LoadGraph("data/image/Margin1.png");
		_marginHandle[MULTI_MODE] = LoadGraph("data/image/Margin2.png");
		_marginHandle[TUTORIAL_MODE] = LoadGraph("data/image/Margin3.png");
		_marginHandle[OPTION_MODE] = LoadGraph("data/image/Margin4.png");
	}

	// ボタン画像の座標を設定する
	_buttonPos[SOLO_MODE] = Vec2{ 202, 118 };
	_buttonPos[MULTI_MODE] = Vec2{ 976, 118 };
	_buttonPos[TUTORIAL_MODE] = Vec2{ 202, 631 };
	_buttonPos[OPTION_MODE] = Vec2{ 976, 631 };

	// 中央の円の座標
	_circlePos = Vec2{ 960,620 };

	// 最初に選択されている項目の設定
	_selectButtonNum = TUTORIAL_MODE;
	_oldSelectButtonNum = _selectButtonNum;
}

SelectModeUi::~SelectModeUi()
{
	// 画像の削除
	for (auto& handle : _buttonHandle) {
		DeleteGraph(handle);
	}
	for (auto& handle : _messageHandle) {
		DeleteGraph(handle);
	}
}

void SelectModeUi::Update()
{
	// 選択されているボタンによって角度を変える
	switch (_selectButtonNum)
	{
	case SOLO_MODE:
		_circleAngle = GetRadian(SOLO_ANGLE);
		break;
	case MULTI_MODE:
		_circleAngle = GetRadian(MULTI_ANGLE);
		break;
	case TUTORIAL_MODE:
		_circleAngle = GetRadian(TUTORIAL_ANGLE);
		break;
	case OPTION_MODE:
		_circleAngle = GetRadian(OPTION_ANGLE);
		break;
	default:
		break;
	}

	// スティックで選択を切り替える
	Vec3 stick = Input::GetInstance().GetStickVector(INPUT_LEFT_STICK, INPUT_PAD_1);

	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > 10000.0f) {
		if (stick.x < 0.0f && stick.z > 0.0f) {
			_selectButtonNum = SOLO_MODE;
		}
		else if (stick.x > 0.0f && stick.z > 0.0f) {
			_selectButtonNum = MULTI_MODE;
		}
		else if (stick.x < 0.0f && stick.z < 0.0f) {
			_selectButtonNum = TUTORIAL_MODE;
		}
		else if (stick.x > 0.0f && stick.z < 0.0f) {
			_selectButtonNum = OPTION_MODE;
		}

		// フレームを初期化
		if (_oldSelectButtonNum != _selectButtonNum) {
			_frame = 0;
			SoundManager::GetInstance().RingSE(SE_NUM_SELECT);
		}

		// 変更フラグを立てる
		_changeFrag = true;
	}
	_oldSelectButtonNum = _selectButtonNum;

	// 変更フラグが立っていたらフレームを加算する
	if (_changeFrag) _frame++;

	// 既定のフレーム数を超えたら
	if (_frame > 30) {
		_changeFrag = false;
	}
	else {
		// フレームで拡大率の増減を切り替える
		if (_frame < 3) {
			_circleScale = 0.7;
		}
		else {
			_circleScale += 0.05;
			_circleScale = min(1.0, _circleScale);
		}

		// フレームの加算
		_frame++;
	}
}

void SelectModeUi::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ボタンのハイライトの描画
	DrawGraph(_buttonPos[_selectButtonNum].intX(), _buttonPos[_selectButtonNum].intY(), _highlightHandle[_selectButtonNum], true);

	// ボタンの描画
	for (int i = 0; i < 4; i++) {
		//DrawRotaGraph(_buttonPos[i].intX(), _buttonPos[i].intY(), 1.0f, 0.0, _buttonHandle[i], true);
		DrawGraph(_buttonPos[i].intX(), _buttonPos[i].intY(), _buttonHandle[i], true);
	}

	// 中央の円の描画
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), 1.0, 0.0, _marginHandle[_selectButtonNum], true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, _circleAngle, _circleHandle[_selectButtonNum], true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, 0.0, _circleLogoHandle, true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, _circleAngle, _centerArrowHandle[_selectButtonNum], true);

	// 下の四角の描画
	DrawBox(0, 986, 1920, 1080, 0x000000, true);

	// 下のメッセージハンドル
	DrawRotaGraph(960, 1033, 1.0, 0.0, _messageHandle[_selectButtonNum], true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1));
}

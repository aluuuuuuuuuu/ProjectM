#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"

SceneSelect::SceneSelect():
	_flame(60)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeDraw;

	// カメラのニアファーの設定
	SetCameraNearFar(1, 512);

	for (auto& select : _finishSelect) {
		select = false;
	}

	// 最初の人数はかならず一人
	_plData.playerNum = 1;


	back = LoadGraph("data/image/back.jpg");
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::PlayerNumSelectUpdate()
{
	// Bボタンで人数の切り替え
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_plData.playerNum == Input::GetInstance().GetPadNum()) {
			_plData.playerNum = 1;
		}
		else {
			_plData.playerNum++;
		}
	}

	// Aボタンで次の画面へ
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// 指のインスタンスを人数分作成する
		for (int i = 0; i < _plData.playerNum; i++) {
			_pFinger[i] = std::make_shared<SelectFinger>(i);
		} 
		
		// カードのインスタンスをキャラクター分作成する
		for (int i = 0; i < 4; i++) {
			_pCard[i] = std::make_shared<CharactorCard>(i + 1);
		}

		// キャラクター選択に移行
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
	}
}

void SceneSelect::PlayerNumSelectDraw() const
{
	switch (_plData.playerNum)
	{
	case 1:
		DrawFormatString(10, 10, 0xffffff, "1人");
		break;
	case 2:
		DrawFormatString(10, 30, 0xffffff, "2人");
		break;
	case 3:
		DrawFormatString(10, 50, 0xffffff, "3人");
		break;
	case 4:
		DrawFormatString(10, 70, 0xffffff, "4人");
		break;
	default:
		break;
	}

	DrawCircle(800, 400, 200, 0x000000);
}

void SceneSelect::CharactorSelectUpdate()
{
	// 全指の更新処理
	for (int num = 0; num < _plData.playerNum; num++) {
		_pFinger[num]->Update();
	}
}

void SceneSelect::CharactorSelectDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, back,true);

	// 全カードの描画
	for (auto& card : _pCard) {
		card->Draw();
	}

	// 全指の描画
	for (int num = 0; num < _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::PlayerNumSelectUpdate;
		_drawFunc = &SceneSelect::PlayerNumSelectDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_plData));
	}
}

void SceneSelect::FadeDraw() const
{
	DrawCircle(800, 400, 200, 0x000000);

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

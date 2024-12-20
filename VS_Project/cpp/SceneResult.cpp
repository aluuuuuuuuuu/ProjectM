#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"
#include "ResultCharactor.h"

SceneResult::SceneResult(PlayerData data, int gameTime):
	_playerData(data),
	_flame(0)
{
	// キャラクターの作成
	_pCharactor = std::make_shared<ResultCharactor>(1);

	// 数字の作成
	_pNum = std::make_shared<NumUtility>(Vec2{10,350},gameTime);

	// リザルトUIの作成
	_pResultUi = std::make_shared<ResultUi>(gameTime);

	_updateFunc = &SceneResult::NormalUpdate;
	_drawFunc = &SceneResult::NormalDraw;
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	(this->*_updateFunc)();
}

void SceneResult::Draw() const
{
	(this->*_drawFunc)();
}

void SceneResult::NormalUpdate()
{
	// Aボタンが押されたらリスタート
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		_nextScece = std::make_shared<SceneTest>(_playerData);
		_updateFunc = &SceneResult::FadeOutUpdate;
		_drawFunc = &SceneResult::FadeDraw;
	}

	// Bボタンが押されたらタイトル画面
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		_nextScece = std::make_shared<SceneTitle>();
		_updateFunc = &SceneResult::FadeOutUpdate;
		_drawFunc = &SceneResult::FadeDraw;
	}

	// STARTボタンが押されたらメニューを開く
	if (Input::GetInstance().IsTrigger(INPUT_START, INPUT_PAD_1)) {
		_nextScece = std::make_shared<SceneMenu>(INPUT_PAD_1);
		_updateFunc = &SceneResult::FadeOutUpdate;
		_drawFunc = &SceneResult::FadeDraw;
	}

	// キャラクターの更新処理
	_pCharactor->Update();
}

void SceneResult::NormalDraw() const
{
	// キャラクターの描画
	_pCharactor->Draw();

	// リザルトUIの描画
	_pResultUi->Draw();

	// 数字の描画
	_pNum->Draw();

#ifdef _DEBUG
	DrawString(10, 10, "Aボタンでリスタート", 0xffffff);
	DrawString(10, 40, "Bボタンでタイトル画面へ", 0xffffff);
	DrawString(10, 70, "STARTボタンでメニュー", 0xffffff);
#endif // DEBUG
}

void SceneResult::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 110) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerData));
	}
}

void SceneResult::FadeDraw() const
{
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

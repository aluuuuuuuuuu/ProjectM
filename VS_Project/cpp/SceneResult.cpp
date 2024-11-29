#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"

SceneResult::SceneResult(PlayerData data):
	_playerData(data)
{
	_pNum = std::make_shared<NumUtility>(Vec2{165,320});
	_pResultUi = std::make_shared<ResultUi>();
	test = LoadGraph("data/image/a.png");
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	// Aボタンが押されたらリスタート
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerData));
	}

	// Bボタンが押されたらタイトル画面
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
	}
	
	// STARTボタンが押されたらメニューを開く
	if (Input::GetInstance().IsTrigger(INPUT_START, INPUT_PAD_1)) {
		SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(INPUT_PAD_1));
	}

	// 数字表示の更新処理
	_pNum->Update(333333);
}

void SceneResult::Draw() const
{
	DrawGraph(0, 0, test, true);
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

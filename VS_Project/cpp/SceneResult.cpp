#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"
#include "ResultCharacter.h"
#include "SoundManager.h"

SceneResult::SceneResult(PlayerData data, int gameTime) :
	_playerData(data),
	_flame(0),
	_nextScene(0)
{
	// キャラクターの作成
	_pCharacter = std::make_shared<ResultCharacter>(data.winner);

	// 数字の作成
	_pNum = std::make_shared<NumUtility>(1.0f, Vec2{ 10,350 }, gameTime);

	// リザルトUIの作成
	_pResultUi = std::make_shared<ResultUi>(gameTime);

	// 関数ポインタの初期化
	_updateFunc = &SceneResult::StartUpdate;
	_drawFunc = &SceneResult::StartDraw;

	// シングルの再生
	SoundManager::GetInstance().RingSE(SE_RESULT);
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

void SceneResult::StartUpdate()
{

	for (int num = 0; num <= _playerData.playerNum; num++) {

		// Aボタンが押されたらリスタート
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {
			_nextScene = SCENE_TEST;
			_updateFunc = &SceneResult::FadeOutUpdate;
			_drawFunc = &SceneResult::FadeOutDraw;
		}

		// Bボタンが押されたらタイトル画面
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {
			_nextScene = SCENE_TITLE;
			_updateFunc = &SceneResult::FadeOutUpdate;
			_drawFunc = &SceneResult::FadeOutDraw;
		}

		// STARTボタンが押されたらメニューを開く
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}

	// キャラクターの更新処理
	_pCharacter->Update();
}

void SceneResult::StartDraw() const
{
	// キャラクターの描画
	_pCharacter->Draw();

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

	// フェードが終了したら
	if (_flame >= 110) {
		// 次のシーンに切り替える
		switch (_nextScene)
		{
		case SCENE_TEST:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerData));
			break;
		case SCENE_TITLE:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
			break;
		default:
			break;
		}
	}
}

void SceneResult::FadeOutDraw() const
{
	StartDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

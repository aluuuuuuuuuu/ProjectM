#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "CharactorSelectManager.h"

SceneSelect::SceneSelect():
	_flame(60)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeInDraw;

	// プレイヤーデータの初期化
	for (auto& pl : _plData.player) {
		pl = -1;
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

		// セレクトマネージャーの作成
		_pSelectManager = std::make_shared<CharactorSelectManager>(_plData);

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
	// セレクトマネージャーの更新
	_pSelectManager->Update();

	// スタートボタンが押されたらゲームシーンに移行する
	if (_pSelectManager->GetStart()) {

		// プレイヤーデータを作成する
		_pSelectManager->CreateData();

		// フェードアウトに移行
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}
}

void SceneSelect::CharactorSelectDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, back,true);

	// セレクトマネージャーの描画処理
	_pSelectManager->Draw();
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

void SceneSelect::FadeInDraw() const
{
	PlayerNumSelectDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::FadeOutDraw() const
{
	CharactorSelectDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

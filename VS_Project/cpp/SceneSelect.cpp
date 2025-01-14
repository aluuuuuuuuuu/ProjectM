#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharacterCard.h"
#include "CharacterSelectManager.h"
#include "SelectUI.h"
#include "SceneTitle.h"

SceneSelect::SceneSelect(int num) :
	_flame(60),
	_nextScene(0)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeInDraw;

	// プレイヤーデータの初期化
	for (auto& pl : _plData.character) {
		pl = -1;
	}
	_plData.playerNum = num;


	// インスタンスの作成
	{
		_pSelectManager = std::make_shared<CharacterSelectManager>(_plData);	// セレクトマネージャー
		_pUi = std::make_shared<SelectUI>();	// ui
	}

	// 背景画像のロード
	back = LoadGraph("data/image/back.jpg");
}

SceneSelect::~SceneSelect()
{
	DeleteGraph(back);
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::CharacterSelectUpdate()
{
	// セレクトマネージャーの更新
	_pSelectManager->Update();

	// スタートボタンが押されたらゲームシーンに移行する
	if (_pSelectManager->GetStart()) {

		// プレイヤーデータを作成する
		_pSelectManager->CreateData();

		// 次のシーンをセレクトシーンに切り替える
		_nextScene = SCENE_TEST;

		// フェードアウトに移行
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}

	// マネージャーの戻るフラグが立っていたら人数選択に戻る
	if (_pSelectManager->GetReturnFlag()) {

		// 次のシーンをタイトルシーンに切り替える
		_nextScene = SCENE_TITLE;

		// フェードアウトに移行
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}
}

void SceneSelect::CharacterSelectDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, back, true);

	// uiの描画
	_pUi->Draw();

	// セレクトマネージャーの描画処理
	_pSelectManager->Draw();
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::CharacterSelectUpdate;
		_drawFunc = &SceneSelect::CharacterSelectDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {

		// 次のシーンに移行する
		switch (_nextScene)
		{
		case SCENE_TITLE:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
			break;
		case SCENE_TEST:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_plData));
			break;
		default:
			break;
		}
	}
}

void SceneSelect::FadeInDraw() const
{
	// 通常の描画も行う
	CharacterSelectDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::FadeOutDraw() const
{
	// 通常の描画も行う
	CharacterSelectDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

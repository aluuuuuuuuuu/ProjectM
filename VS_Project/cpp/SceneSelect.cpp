#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "CharactorSelectManager.h"
#include "SelectUI.h"

SceneSelect::SceneSelect(int num):
	_flame(60)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeInDraw;

	// プレイヤーデータの初期化
	for (auto& pl : _plData.charactor) {
		pl = -1;
	}
	_plData.playerNum = num;

	// セレクトマネージャーの作成
	_pSelectManager = std::make_shared<CharactorSelectManager>(_plData);

	// uiインスタンスの作成
	_pUi = std::make_shared<SelectUI>();

	// 背景画像のロード
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

	// uiの描画
	_pUi->Draw();

	// セレクトマネージャーの描画処理
	_pSelectManager->Draw();
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
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
	CharactorSelectDraw();

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

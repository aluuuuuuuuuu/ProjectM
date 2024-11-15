#include "SceneMenu.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "MenuManager.h"

SceneMenu::SceneMenu(int padNum):
	_padNum(padNum),
	_flame(0)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneMenu::FadeInUpdate;
	_drawFunc = &SceneMenu::FadeDraw;

	// メニューマネージャーのポインタを作成
	_pManager = std::make_shared<MenuManager>(_padNum);

	// 背景ぼかし画像
	_backHandle = LoadGraph("data/image/backBloom.png");
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Update()
{
	(this->*_updateFunc)();
}

void SceneMenu::Draw() const
{
	(this->*_drawFunc)();
}

void SceneMenu::NormalUpdate()
{
	// スタートボタンを押すとフェードアウトする
	if (Input::GetInstance().IsTrigger(INPUT_START, _padNum)) {
		_updateFunc = &SceneMenu::FadeOutUpdate;
		_drawFunc = &SceneMenu::FadeDraw;
	}

	// マネージャーの更新処理
	_pManager->Update();
}

void SceneMenu::NormalDraw() const
{
	// ぼかしの描画
	DrawGraph(1, 0, _backHandle, true);

	// メニューマネージャーの描画処理
	_pManager->Draw();
}

void SceneMenu::FadeInUpdate()
{
	// マネージャーの更新処理
	_pManager->Update();

	_flame++;
	if (_flame >= 5) {
		_updateFunc = &SceneMenu::NormalUpdate;
		_drawFunc = &SceneMenu::NormalDraw;
	}
}

void SceneMenu::FadeOutUpdate()
{
	// マネージャーの更新処理
	_pManager->Update();

	_flame--;
	if (_flame <= 0) {
		SceneManager::GetInstance().PopScene();
	}
}

void SceneMenu::FadeDraw() const
{
	// ぼかしの描画
	DrawGraph(0, 0, _backHandle, true);

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 5));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// メニューマネージャーの描画処理
	_pManager->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

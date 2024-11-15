#include "MenuManager.h"
#include "DxLib.h"
#include "SelectFinger.h"
#include "Application.h"
#include "MenuButton.h"

MenuManager::MenuManager(int padNum)
{
	// 選択指のポインタの作成
	_pFinger = std::make_shared<SelectFinger>(padNum);

	// 基盤画像のロード
	_menuBordHandle = LoadGraph("data/image/Bord.png");

	// 基盤画像の座標を取得
	_bordPos.x = (Application::GetInstance().GetConstantInt("SCREEN_WIDTH")) / 2;
	_bordPos.y = (Application::GetInstance().GetConstantInt("SCREEN_HEIGHT")) / 2;

	// 各ボタンの作成と初期設定
	_pButton[0] = std::make_shared<MenuButton>(Vec2{ 1377,300 }, Vec2{ 260,230 }, LoadGraph("data/image/Cancel.png"), BATU_BUTTON);
	_pButton[1] = std::make_shared<MenuButton>(Vec2{ 725,_bordPos.intY() }, Vec2{ 530,190 }, LoadGraph("data/image/Manual.png"), MANUAL_BUTTON);
	_pButton[2] = std::make_shared<MenuButton>(Vec2{ 1200,_bordPos.intY() }, Vec2{ 160,150 }, LoadGraph("data/image/Bolume.png"), SE_BUTTON);
	_pButton[3] = std::make_shared<MenuButton>(Vec2{ 1400,_bordPos.intY() }, Vec2{ 160,150 }, LoadGraph("data/image/BGM.png"), BGM_BUTTON);
	_pButton[4] = std::make_shared<MenuButton>(Vec2{ _bordPos.intX(),800 }, Vec2{ 680,120 }, LoadGraph("data/image/End.png"), END_BUTTON);
}

MenuManager::~MenuManager()
{
	DeleteGraph(_menuBordHandle);
}

void MenuManager::Update()
{
	// 指の描画
	_pFinger->Update();
}

void MenuManager::Draw() const
{
	// 基盤の描画
	DrawRotaGraph(_bordPos.intX(), _bordPos.intY(), 1.0, 0.0, _menuBordHandle, true);

	for (auto& button : _pButton) {
		button->Draw();
	}

	// 指の描画
	_pFinger->Draw();
}

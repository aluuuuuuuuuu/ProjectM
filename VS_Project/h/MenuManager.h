#pragma once
#include <memory>
#include "Vec2.h"

#define BATU_BUTTON 0
#define MANUAL_BUTTON 1
#define SE_BUTTON 2
#define BGM_BUTTON 3
#define END_BUTTON 4

class MenuButton;
class SelectFinger;
class MenuManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="padNum">操作するパッドナンバー</param>
	MenuManager(int padNum);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~MenuManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;


private:

	// メニューの基盤画像
	int _menuBordHandle;

	// 基盤の表示座標
	Vec2 _bordPos;

	// 選択指のポインタ
	std::shared_ptr<SelectFinger> _pFinger;

	// 選択ボタン
	std::shared_ptr<MenuButton> _pButton[5];
};


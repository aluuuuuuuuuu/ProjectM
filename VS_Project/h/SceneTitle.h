#pragma once
#include "SceneBase.h"
#include "Components.h"
#include <memory>

class Crown;
class SceneTitle :
	public SceneBase
{
public:

    SceneTitle();
    virtual ~SceneTitle();

    void Update();
    void Draw() const;
private:

	// 関数ポインタ
	using _UpdateFunc_t = void (SceneTitle::*)();
	using _DrawFunc_t = void (SceneTitle::*)() const;

	// 任意のアップデート関数変数、ドロー関数変数
	_UpdateFunc_t _updateFunc = nullptr;
	_DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// 通常の更新処理
	/// </summary>
	void NormalUpdate();

	/// <summary>
	/// 通常の描画処理
	/// </summary>
	void NormalDraw() const;

	/// <summary>
	/// フェードイン更新処理
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// フェードアウト更新処理
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// フェード共通の描画処理
	/// </summary>
	void FadeDraw() const;

	// タイトルロゴハンドル
	int _logoHandle;

	// anybutton画像ハンドル
	int _guideHandle;

	// フェード用フレームカウンタ
	int _flame;

	// 背景画像
	int _backgroundHandle;

	// 画面サイズ
	int _windowWidth;	// 画面幅
	int _windowHeight;	// 画面高さ

	// 王冠ポインタ
	std::shared_ptr<Crown> _pCrown;
};


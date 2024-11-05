#pragma once
#include "SceneBase.h"
#include "Components.h"
#include <memory>
#include "Constant.h"

class AnyPushButton;
class Logo;
class Crown;
class SceneTitle :
	public SceneBase,
	public Constant
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneTitle();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneTitle();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
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

	// 王冠ポインタ
	std::shared_ptr<Crown> _pCrown;

	// ロゴポインタ
	std::shared_ptr<Logo> _pLogo;

	// 文章ポインタ
	std::shared_ptr<AnyPushButton> _pText;

	// フェード用フレームカウンタ
	int _flame;

	// 背景画像
	int _backgroundHandle;
};


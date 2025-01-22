#pragma once
#include "SceneBase.h"
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"

class SkyDome;
class FallCharactor;
class NumSelectButton;
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
	SceneTitle(bool slidInFlag);

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
	void StartUpdate();

	/// <summary>
	/// 通常の描画処理
	/// </summary>
	void StartDraw() const;

	/// <summary>
	/// スライドインの更新処理
	/// </summary>
	void SlideInUpdate();

	/// <summary>
	/// スライドアウトの更新処理
	/// </summary>
	void SlideOutUpdate();

	/// <summary>
	///	スライドインの描画処理
	/// </summary>
	void SlideInDraw() const;

	/// <summary>
	/// スライドアウトの描画処理
	/// </summary>
	void SlideOutDraw() const;

	/// <summary>
	/// フェードイン更新処理
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// フェードアウト更新処理
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// フェードイン描画処理
	/// </summary>
	void FadeInDraw() const;

	/// <summary>
	/// フェードアウト描画処理
	/// </summary>
	void FadeOutDraw() const;

	/// <summary>
	/// 人数セレクトの更新処理
	/// </summary>
	void NumSelectUpdate();

	/// <summary>
	/// 人数セレクトの描画処理
	/// </summary>
	void NumSelectDraw() const;

	// 王冠ポインタ
	std::shared_ptr<Crown> _pCrown;

	// ロゴポインタ
	std::shared_ptr<Logo> _pLogo;

	// 文章ポインタ
	std::shared_ptr<AnyPushButton> _pText;

	// 人数セレクトポインタ
	std::shared_ptr<NumSelectButton> _pNum;

	// 落下キャラクターポインタ
	std::shared_ptr<FallCharactor> _pFallCharactor;

	// スカイドームポインタ
	std::shared_ptr<SkyDome> _pSkyDome;

	// フェード用フレームカウンタ
	int _flame;

	// スライド画像ハンドル
	int _slideHandle;

	// スライドイン画像の座標
	Vec2 _slidePos;

	// スライドインフラグ
	bool _selectDrawFlag;

	// 背景画像ハンドル
	int _backHandle;

};


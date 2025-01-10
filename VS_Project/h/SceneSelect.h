#pragma once
#include "SceneBase.h"
#include "PlayerManager.h"
#include <memory>

constexpr int CHARACTOR_1 = 1;
constexpr int CHARACTOR_2 = 2;
constexpr int CHARACTOR_3 = 3;
constexpr int CHARACTOR_4 = 4;

class SelectUI;
class CharactorSelectManager;
class CharactorCard;
class SelectFinger;
class SceneSelect :
    public SceneBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="num">プレイヤー数</param>
    SceneSelect(int num);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneSelect();

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
    using _UpdateFunc_t = void (SceneSelect::*)();
    using _DrawFunc_t = void (SceneSelect::*)() const;

    // 任意のアップデート関数変数、ドロー関数変数
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// キャラクター選択時の更新処理
	/// </summary>
	void CharactorSelectUpdate();

	/// <summary>
	/// キャラクター選択時の描画処理
	/// </summary>
	void CharactorSelectDraw() const;

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
	void FadeInDraw	() const;

	/// <summary>
	/// フェードアウト描画処理
	/// </summary>
	void FadeOutDraw() const;

	// キャラセレクトマネージャー
	std::shared_ptr<CharactorSelectManager> _pSelectManager;

	// フェード用フレームカウンタ
	int _flame;

	// ゲームシーンに渡すプレイヤーのデータ
	PlayerData _plData;

	// uiクラスポインタ
	std::shared_ptr<SelectUI> _pUi;

	int back;

};


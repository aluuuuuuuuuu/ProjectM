#pragma once
#include "SceneBase.h"

constexpr int CHARACTOR_1 = 1;
constexpr int CHARACTOR_2 = 2;
constexpr int CHARACTOR_3 = 3;
constexpr int CHARACTOR_4 = 4;

struct Player
{
	// キャラ選択フラグ
	bool selectFlag = false;

	// 選択キャラクター種
	int selectCharactor = 0;

};

class SceneSelect :
    public SceneBase
{
public:
    SceneSelect();
    virtual ~SceneSelect();

    void Update();
    void Draw() const;
private:

    // 関数ポインタ
    using _UpdateFunc_t = void (SceneSelect::*)();
    using _DrawFunc_t = void (SceneSelect::*)() const;

    // 任意のアップデート関数変数、ドロー関数変数
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// プレイヤー数選択時の更新処理
	/// </summary>
	void PlayerNumSelectUpdate();

	/// <summary>
	/// プレイヤー数選択時の描画処理
	/// </summary>
	void PlayerNumSelectDraw() const;

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
	/// フェード共通の描画処理
	/// </summary>
	void FadeDraw() const;

	// フェード用フレームカウンタ
	int _flame;

	// 人数選択
	int _playerNum;

	// 最大人数分のプレイヤー構造体
	Player _player[4];

	// キャラクター数に応じた選択フラグ
	bool _finishSelect[4];
};


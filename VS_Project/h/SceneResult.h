#pragma once
#include "SceneBase.h"
#include <memory>
#include "PlayerManager.h"

class ResultCharacter;
class NumUtility;
class ResultUi;
class SceneResult :
	public SceneBase
{
public:


	SceneResult(PlayerData data, int gameTime);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SceneResult();

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
	using _UpdateFunc_t = void (SceneResult::*)();
	using _DrawFunc_t = void (SceneResult::*)() const;

	// 任意のアップデート関数変数、ドロー関数変数
	_UpdateFunc_t _updateFunc = nullptr;
	_DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// 通常の更新処理
	/// </summary>
	void NomalUpdate();

	/// <summary>
	/// 通常の描画処理
	/// </summary>
	void NormalDraw() const;

	/// <summary>
	/// フェード用の更新処理
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// フェード用の描画処理
	/// </summary>
	void FadeOutDraw() const;


	// 数字利用ポインタ
	std::shared_ptr<NumUtility> _pNum;

	// リザルトロゴポインタ
	std::shared_ptr<ResultUi> _pResultUi;

	// プレイヤーデータを保持する
	PlayerData _playerData;

	// キャラクター
	std::shared_ptr<ResultCharacter> _pCharacter;

	// フレームカウンタ
	int _flame;

	// 次にロードするシーン
	int _nextScene;
};


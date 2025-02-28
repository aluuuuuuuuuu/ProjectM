#pragma once
#include <memory>
#include "Vec2.h"

constexpr int GUIDE_CAMERA = 0;
constexpr int GUIDE_MOVE = 1;
constexpr int GUIDE_JUMP = 2;
constexpr int GUIDE_SHOT = 3;

class WedgewormManager;
class StageManager;
class StageCollisionManager;
class BulletManager;
class MapBulletCollisionManager;
class PlayerManager;
class SkyDome;
class TutorialManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialManager();

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
	using _updateFunc_t = void (TutorialManager::*)();
	using _drawFunc_t = void (TutorialManager::*)() const;

	// 任意のアップデート関数変数、ドロー関数変数
	_updateFunc_t _updateFunc = nullptr;
	_drawFunc_t  _drawFunc = nullptr;

	void CameraUpdate();

	void MoveUpdate();

	void JumpUpdate();

	void ShotUpdate();

	void SelectUpdate();

	void LastUpdate();

	void ShareDraw() const;

	/// <summary>
	/// クリアしたときの処理
	/// </summary>
	/// <returns>Aボタンが押されたらtrueを返す</returns>
	bool ClearFunction();

	// デフォルトの処理
	void DefaultUpdate();

	// ステージポインタ
	std::shared_ptr<StageManager> _pStage;

	// ステージコリジョンマネージャポインタ
	std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

	// バレットマネージャポインタ
	std::shared_ptr<BulletManager> _pBulletManager;

	// バレットコリジョンマネージャー
	std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

	// プレイヤーマネージャー
	std::shared_ptr<PlayerManager> _pPlayerManager;

	// スカイドームポインタ
	std::shared_ptr<SkyDome> _pSkyDome;

	// 禊虫マネージャー
	std::shared_ptr<WedgewormManager> _pWedgewormManager;

	// フレームカウンタ
	int _frame;

	// チュートリアルのガイド文章画像ハンドル
	int _guideHandle[5];

	// ガイド文章の座標
	Vec2 _guidePos;

	// チュートリアルの進行度
	int _tutorialProgress;

	// クリア画像の座標
	Vec2 _clearPos;

	// クリア画像のハンドル
	int _clearHandle;

	// 既定の処理を行ったフラグ
	bool _endFrag;

	// クリア画像のScale
	double _clearScale;

};
 
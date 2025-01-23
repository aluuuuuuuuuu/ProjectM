#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>
#include <vector>

class BulletManager;
class NumUtility;
class GameFlowManager;
class WedgewormManager;
class SkyDome;
class PlayerManager;
class MapBulletCollisionManager;
class StageCollisionManager;
class StageManager;
struct PlayerData;
class ScenePve :
    public SceneBase,
	public Constant
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="data">プレイヤーデータ</param>
	ScenePve(PlayerData& data);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ScenePve();

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
	using m_updateFunc_t = void (ScenePve::*)();
	using m_drawFunc_t = void (ScenePve::*)() const;
	m_updateFunc_t _updateFunc = nullptr;
	m_drawFunc_t _drawFunc = nullptr;

	/// <summary>
	/// 通常の更新処理
	/// </summary>
	void NomalUpdate();

	/// <summary>
	/// 通常の描画処理
	/// </summary>
	void NormalDraw() const;

	/// <summary>
	/// ゲーム終了時の更新処理
	/// </summary>
	void EndUpdate();

	/// <summary>
	/// ゲーム終了時の描画処理
	/// </summary>
	void EndDraw() const;

	/// <summary>
	/// ゲームフローマネージャー
	/// </summary>
	std::shared_ptr<GameFlowManager> _pGameFlowManager;

	/// <summary>
	/// プレイヤーマネージャー
	/// </summary>
	std::shared_ptr<PlayerManager> _pPlayerManager;

	/// <summary>
	/// ステージマネージャー
	/// </summary>
	std::shared_ptr<StageManager> _pStage;

	/// <summary>
	/// バレットマネージャー
	/// </summary>
	std::shared_ptr<BulletManager> _pBulletManager;

	/// <summary>
	/// バレットコリジョンマネージャー
	/// </summary>
	std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

	/// <summary>
	/// ステージコリジョンマネージャー
	/// </summary>
	std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

	/// <summary>
	/// 禊虫マネージャー
	/// </summary>
	std::shared_ptr<WedgewormManager> _pWedgewormManager;

	/// <summary>
	/// スカイドーム
	/// </summary>
	std::shared_ptr<SkyDome> _pSkyDome;

	/// <summary>
	/// 数字ユーティリティ
	/// </summary>
	std::shared_ptr<NumUtility> _pNum;
};


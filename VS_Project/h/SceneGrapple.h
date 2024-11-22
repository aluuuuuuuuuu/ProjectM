#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>
#include "Components.h"
#include <vector>
#include "PlayerManager.h"

class GameFlowManager;
class WedgewormManager;
class SkyDome;
class PlayerManager;
class MapBulletCollisionManager;
class BulletManager;
class StageCollisionManager;
class StageManager;
class SceneGrapple :
    public SceneBase
{
public:
    SceneGrapple();

    virtual ~SceneGrapple();

    void Update();

    void Draw() const;
private:
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

    // ゲームフローマネージャー
    std::shared_ptr<GameFlowManager> _pGameFlowManager;
};


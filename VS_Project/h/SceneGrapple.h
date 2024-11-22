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
    // �X�e�[�W�|�C���^
    std::shared_ptr<StageManager> _pStage;

    // �X�e�[�W�R���W�����}�l�[�W���|�C���^
    std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

    // �o���b�g�}�l�[�W���|�C���^
    std::shared_ptr<BulletManager> _pBulletManager;

    // �o���b�g�R���W�����}�l�[�W���[
    std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

    // �v���C���[�}�l�[�W���[
    std::shared_ptr<PlayerManager> _pPlayerManager;

    // �X�J�C�h�[���|�C���^
    std::shared_ptr<SkyDome> _pSkyDome;

    // �S���}�l�[�W���[
    std::shared_ptr<WedgewormManager> _pWedgewormManager;

    // �Q�[���t���[�}�l�[�W���[
    std::shared_ptr<GameFlowManager> _pGameFlowManager;
};


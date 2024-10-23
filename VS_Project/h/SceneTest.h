#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>

class MapBulletCollisionManager;
class BulletManager;
class StageCollisionManager;
class Player;
class StageManager;
class SceneTest :
    public SceneBase,
    public Constant
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneTest();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneTest();

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() const;

private:
    /// <summary>
    /// �O���b�h�\��
    /// </summary>
    void DrawGrid() const;

    // �֐��|�C���^
    using m_updateFunc_t = void (SceneTest::*)();
    using m_drawFunc_t = void (SceneTest::*)() const;
    m_updateFunc_t _updateFunc = nullptr;
    m_drawFunc_t _drawFunc = nullptr;

    /// <summary>
    /// �ʏ�̍X�V����
    /// </summary>
    void NormalUpdate();

    /// <summary>
    /// �ʏ�̕`�揈��
    /// </summary>
    void NormalDraw() const;

    // �X�e�[�W�|�C���^
    std::shared_ptr<StageManager> _pStage;

    // �v���C���[�|�C���^
    std::shared_ptr<Player> _pPlayer;
    std::shared_ptr<Player> _pPlayer1;

    // �X�e�[�W�R���W�����}�l�[�W���|�C���^
    std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

    // �o���b�g�}�l�[�W���|�C���^
    std::shared_ptr<BulletManager> _pBulletManager;

    // �o���b�g�R���W�����}�l�[�W���[
    std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

};


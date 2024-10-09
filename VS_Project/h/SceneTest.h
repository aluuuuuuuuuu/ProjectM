#pragma once
#include "SceneBase.h"
#include <memory>

class EnemyManager;
class MapCollisionManager;
class StaticObjectManager;
class Direction;
class Player;
// �e�X�g�V�[��
class SceneTest :
    public SceneBase
{
public:
    SceneTest();
    virtual ~SceneTest();

    void Update();
    void Draw() const;

    void DrawGrid() const;
private:

    // �֐��|�C���^
    using m_updateFunc_t = void (SceneTest::*)();
    using m_drawFunc_t = void (SceneTest::*)() const;
    m_updateFunc_t m_updateFunc = nullptr;
    m_drawFunc_t m_drawFunc = nullptr;

    // �ʏ�̏���
    void NormalUpdate();
    void NormalDraw() const;

    // �V�[�P���X���̏���
    void SeqUpdate();
    void SeqDraw() const;

    // �v���C���[�̃|�C���^
    std::shared_ptr<Player> m_pPlayer;

    // �f�B���N�V�����̂ۃC���^
    std::shared_ptr<Direction> m_pDirection;

    // �X�^�e�B�b�N�I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
    std::shared_ptr<StaticObjectManager> m_pStaticObject;

    // �R���W�����}�l�[�W���[�̃|�C���^
    std::shared_ptr<MapCollisionManager> m_pCollisionManager;

    // �G�l�~�[�}�l�[�W���[�̃|�C���^
    std::shared_ptr<EnemyManager> m_pEnemyManager;
};


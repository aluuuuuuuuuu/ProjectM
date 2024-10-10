#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>

class Player;
class Stage;
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
    std::shared_ptr<Stage> _pStage;

    // �v���C���[�|�C���^
    std::shared_ptr<Player> _pPlayer;

};


#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>
#include <vector>

struct VECTOR4
{
    int a;
    int b;
    int c;
    int d;
};

struct VECTOR2
{
    int a;
    int b;
};

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
    /// <param name="playerNum">�v���C���[�̐�</param>
    SceneTest(int playerNum);

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

    /// <summary>
    /// �v���C���[������`��͈͂����߂�
    /// </summary>
    /// <param name="num">�v���C���[�̐�-1/param>
    /// <param name="scWidth">�X�N���[���̕�</param>
    /// <param name="scHeight">�X�N���[���̍���</param>
    /// <returns>�`��͈�</returns>
    VECTOR4 CreateDrawArea(int num, int scWidth, int scHeight);
    
    /// <summary>
    /// �v���C���[������X�N���[���̒��S�����߂�
    /// </summary>
    /// <param name="num">�v���C���[�̐�-1</param>
    /// <param name="scWidth">�X�N���[���̕�</param>
    /// <param name="scHeight">�X�N���[���̍���</param>
    /// <returns>�J�����̒��S</returns>
    VECTOR2 CreateScreenCenter(int num, int scWidth, int scHeight);

    // �X�e�[�W�|�C���^
    std::shared_ptr<StageManager> _pStage;

    // �v���C���[�|�C���^
    std::vector<std::shared_ptr<Player>> _pPlayer;

    // �X�e�[�W�R���W�����}�l�[�W���|�C���^
    std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

    // �o���b�g�}�l�[�W���|�C���^
    std::shared_ptr<BulletManager> _pBulletManager;

    // �o���b�g�R���W�����}�l�[�W���[
    std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

    int _windowWidth;
    int _windowHeight;

    VECTOR4 _drawArea[4];
    VECTOR2 _cameraSenter[4];

};


#pragma once
#include "SceneBase.h"
#include <memory>
#include "Vec2.h"
#include "Constant.h"

class SkyDome;
class SelectModeUi;
class SceneSelectMode :
    public SceneBase,
    public Constant
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="slideInFlag">�X���C�h�C������t���O</param>
    SceneSelectMode(bool slideInFlag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SceneSelectMode();

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
    using _updateFunc_t = void (SceneSelectMode::*)();
    using _drawFunc_t = void (SceneSelectMode::*)() const;

    // �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
    _updateFunc_t _updateFunc = nullptr;
    _drawFunc_t  _drawFunc = nullptr;

    /// <summary>
    /// �ʏ�̍X�V����
    /// </summary>
    void NormalUpdate();

    /// <summary>
    /// �ʏ�̕`�揈��
    /// </summary>
    void NormalDraw() const;

    /// <summary>
    /// �X���C�h�C���̍X�V����
    /// </summary>
    void SlideInUpdate();

    /// <summary>
    /// �X���C�h�A�E�g�̍X�V����
    /// </summary>
    void SlideOutUpdate();

    /// <summary>
    ///	�X���C�h�C���̕`�揈��
    /// </summary>
    void SlideInDraw() const;

    /// <summary>
    /// �X���C�h�A�E�g�̕`�揈��
    /// </summary>
    void SlideOutDraw() const;

    // UI�|�C���^
	std::shared_ptr<SelectModeUi> _pUi;

    // �X�J�C�h�[���|�C���^
    std::shared_ptr<SkyDome> _pSkyDome;

    // �X���C�h�摜�n���h��
    int _slideHandle;

    // �X���C�h�C���摜�̍��W
    Vec2 _slidePos;

    // �^�C�g���V�[���ɖ߂�t���O
    bool _titleFrag;

    // �Z���N�g�V�[������߂����t���O
    bool _returnSelectFrag;

    // �t���[���J�E���^
    int _frame;
};


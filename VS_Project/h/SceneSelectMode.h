#pragma once
#include "SceneBase.h"

class SceneSelectMode :
    public SceneBase
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
    using _UpdateFunc_t = void (SceneSelectMode::*)();
    using _DrawFunc_t = void (SceneSelectMode::*)() const;

    // �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

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

};


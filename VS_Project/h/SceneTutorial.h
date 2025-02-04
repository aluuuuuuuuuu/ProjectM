#pragma once
#include "SceneBase.h"
#include <memory>

class TutorialManager;
class SceneTutorial :
    public SceneBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneTutorial();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SceneTutorial();

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
    using _UpdateFunc_t = void (SceneTutorial::*)();
    using _DrawFunc_t = void (SceneTutorial::*)() const;

    // �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

    void NormalUpdate();

    void NormalDraw() const;

    void FadeInUpdate();

    void FadeOutUpdate();

    void FadeInDraw() const;

    void FadeOutDraw() const;

    // �`���[�g���A���}�l�[�W���[�|�C���^
    std::shared_ptr<TutorialManager> _pManager;


    // �t���[���J�E���^
    int _frame;

};


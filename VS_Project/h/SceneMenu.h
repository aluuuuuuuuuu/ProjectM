#pragma once
#include "SceneBase.h"
#include <memory>

class MenuManager;
class SceneMenu :
    public SceneBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="padNum">���j���[���J�����p�b�h</param>
    SceneMenu(int padNum);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneMenu();

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() const;

private:

    // �֐��|�C���^
    using _UpdateFunc_t = void (SceneMenu::*)();
    using _DrawFunc_t = void (SceneMenu::*)() const;

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
    /// �t�F�[�h�C���X�V����
    /// </summary>
    void FadeInUpdate();

    /// <summary>
    /// �t�F�[�h�A�E�g�X�V����
    /// </summary>
    void FadeOutUpdate();

    /// <summary>
    /// �t�F�[�h���ʂ̕`�揈��
    /// </summary>
    void FadeDraw() const;

    // ���j���[�}�l�[�W���[�̃|�C���^
    std::shared_ptr<MenuManager> _pManager;

    // ���삷��p�b�h
    int _padNum;

    // �w�i�̂ڂ����摜
    int _backHandle;

    // �t�F�[�h�p�t���[���J�E���^
    int _flame;
};

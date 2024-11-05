#pragma once
#include "SceneBase.h"
#include "Components.h"
#include <memory>
#include "Constant.h"

class AnyPushButton;
class Logo;
class Crown;
class SceneTitle :
	public SceneBase,
	public Constant
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneTitle();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneTitle();

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
	using _UpdateFunc_t = void (SceneTitle::*)();
	using _DrawFunc_t = void (SceneTitle::*)() const;

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

	// �����|�C���^
	std::shared_ptr<Crown> _pCrown;

	// ���S�|�C���^
	std::shared_ptr<Logo> _pLogo;

	// ���̓|�C���^
	std::shared_ptr<AnyPushButton> _pText;

	// �t�F�[�h�p�t���[���J�E���^
	int _flame;

	// �w�i�摜
	int _backgroundHandle;
};


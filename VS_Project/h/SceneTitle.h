#pragma once
#include "SceneBase.h"
#include "Components.h"

class SceneTitle :
	public SceneBase,
	public Model,
	public Transform
{
public:

    SceneTitle();
    virtual ~SceneTitle();

    void Update();
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

	// �^�C�g�����S�n���h��
	int _logoHandle;

	// anybutton�摜�n���h��
	int _guideHandle;

	// �t�F�[�h�p�t���[���J�E���^
	int _flame;

	int _modelHandle;

	int _backgroundHandle;


	int _windowWidth;
	int _windowHeight;
};


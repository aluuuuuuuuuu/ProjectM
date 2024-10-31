#pragma once
#include "SceneBase.h"

class SceneSelect :
    public SceneBase
{
public:
    SceneSelect();
    virtual ~SceneSelect();

    void Update();
    void Draw() const;
private:

    // �֐��|�C���^
    using _UpdateFunc_t = void (SceneSelect::*)();
    using _DrawFunc_t = void (SceneSelect::*)() const;

    // �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// �v���C���[���I�����̍X�V����
	/// </summary>
	void PlayerNumSelectUpdate();

	/// <summary>
	/// �v���C���[���I�����̕`�揈��
	/// </summary>
	void PlayerNumSelectDraw() const;

	/// <summary>
	/// �L�����N�^�[�I�����̍X�V����
	/// </summary>
	void CharactorSelectUpdate();

	/// <summary>
	/// �L�����N�^�[�I�����̕`�揈��
	/// </summary>
	void CharactorSelectDraw() const;

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

	// �t�F�[�h�p�t���[���J�E���^
	int _flame;

	// �l���I��
	int _playerNum;

	// �L�����I��
	int _
};


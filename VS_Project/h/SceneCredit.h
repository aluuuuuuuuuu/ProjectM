#pragma once
#include "SceneBase.h"
#include <memory>
#include "Vec2.h"
#include "Constant.h"

class CreditCharacter;
class SceneCredit :
    public SceneBase,
	public Constant
{
public:
    SceneCredit();

    virtual ~SceneCredit();

    void Update();

    void Draw() const;

private:

	// �֐��|�C���^
	using _updateFunc_t = void (SceneCredit::*)();
	using _drawFunc_t = void (SceneCredit::*)() const;

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
	/// �t�F�[�h�C���X�V����
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// �t�F�[�h�A�E�g�X�V����
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�`�揈��
	/// </summary>
	void FadeDraw() const;

	// �N���W�b�g�摜�n���h��
	int _creditHandle;

	// �N���W�b�g�\��Y���W
	int _creditY;

	// �N���W�b�g�t���[���J�E���^
	int _creditFrame;

	// �N���W�b�g�L����
	std::shared_ptr<CreditCharacter> _pChar1;
	std::shared_ptr<CreditCharacter> _pChar2;
	std::shared_ptr<CreditCharacter> _pChar3;
	std::shared_ptr<CreditCharacter> _pChar4;

	// �t�F�[�h�p�t���[���J�E���^
	int _frame;
};


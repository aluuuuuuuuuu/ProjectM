#pragma once
#include "SceneBase.h"
#include "Components.h"
#include <memory>
#include "Constant.h"
#include "Vec2.h"

class CreditCharacter;
class TitlePlayer;
class StageManager;
class SkyDome;
class FallCharactor;
class NumSelectButton;
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
	SceneTitle(bool slidInFlag);

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

	/// <summary>
	/// �t�F�[�h�C���X�V����
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// �t�F�[�h�A�E�g�X�V����
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�C���`�揈��
	/// </summary>
	void FadeInDraw() const;

	/// <summary>
	/// �t�F�[�h�A�E�g�`�揈��
	/// </summary>
	void FadeOutDraw() const;

	/// <summary>
	/// �l���Z���N�g�̍X�V����
	/// </summary>
	void NumSelectUpdate();

	/// <summary>
	/// �l���Z���N�g�̕`�揈��
	/// </summary>
	void NumSelectDraw() const;

	/// <summary>
	/// �N���W�b�g�X�V����
	/// </summary>
	void CreditUpdate();

	/// <summary>
	/// �N���W�b�g�`�揈��
	/// </summary>
	void CreditDraw() const;

	/// <summary>
	/// �ʏ�̃t�F�[�h�C���X�V����
	/// </summary>
	void NormalFadeInUpdate();

	/// <summary>
	/// �ʏ�̃t�F�[�h�A�E�g�X�V����
	/// </summary>
	void NormalFadeOutUpdate();

	/// <summary>
	/// �ʏ�̃t�F�[�h�`�揈��
	/// </summary>
	void NormalFadeDraw() const;

	/// <summary>
	/// �N���W�b�g�t�F�[�h�C���X�V����
	/// </summary>
	void CreditFadeInUpdate();

	/// <summary>
	/// �N���W�b�g�t�F�[�h�A�E�g�X�V����
	/// </summary>
	void CreditFadeOutUpdate();

	/// <summary>
	/// �N���W�b�g�t�F�[�h�`�揈��
	/// </summary>
	void CreditFadeDraw() const;

	// �����|�C���^
	std::shared_ptr<Crown> _pCrown;

	// ���S�|�C���^
	std::shared_ptr<Logo> _pLogo;

	// ���̓|�C���^
	std::shared_ptr<AnyPushButton> _pText;

	// �l���Z���N�g�|�C���^
	std::shared_ptr<NumSelectButton> _pNum;

	// �����L�����N�^�[�|�C���^
	std::shared_ptr<FallCharactor> _pFallCharactor;

	// �X�J�C�h�[���|�C���^
	std::shared_ptr<SkyDome> _pSkyDome;

	// �����̃��f��
	std::shared_ptr<TitlePlayer> _pModel1;
	std::shared_ptr<TitlePlayer> _pModel2;

	// �t�F�[�h�p�t���[���J�E���^
	int _frame;

	// �X���C�h�摜�n���h��
	int _slideHandle;

	// �X���C�h�C���摜�̍��W
	Vec2 _slidePos;

	// �X���C�h�C���t���O
	bool _selectDrawFlag;

	// �w�i�摜�n���h��
	int _backHandle;

	// �N���W�b�g�摜�n���h��
	int _creditHandle;

	// �N���W�b�g�\��Y���W
	int _creditY;

	// �N���W�b�g�t���[���J�E���^
	int _creditFlame;

	// �Z���t�摜�n���h��
	int _serihu;
	int _serihu2;
	int _serihu3;

	// �N���W�b�g�L����
	std::shared_ptr<CreditCharacter> _pChar1;
	std::shared_ptr<CreditCharacter> _pChar2;
	std::shared_ptr<CreditCharacter> _pChar3;
	std::shared_ptr<CreditCharacter> _pChar4;

	// �`���[�g���A���t���O
	bool _tutorial;
};


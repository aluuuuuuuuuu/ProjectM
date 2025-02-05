#pragma once
#include <memory>
#include "Vec2.h"

#define BATU_BUTTON 0
#define MANUAL_BUTTON 1
#define SE_BUTTON 2
#define BGM_BUTTON 3
#define END_BUTTON 4
#define ALL_BUTTON_NUM 5

#define ZERO_GRAPH 0
#define MIN_GRAPH 1
#define MIDDLE_GRAPH 2
#define MAX_GRAPH 3

class MenuCollisionManager;
class MenuButton;
class SelectFinger;
class MenuManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="padNum">���삷��p�b�h�i���o�[</param>
	MenuManager(int padNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MenuManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// ���W���擾����
	/// </summary>
	/// <param name="buttonNum">�{�^���̎�ޔԍ�</param>
	/// <returns>���W</returns>
	Vec2 GetPos(int buttonNum);

	/// <summary>
	/// �����蔻��͈͂��擾����
	/// </summary>
	/// <param name="buttonNum">�{�^���̎�ޔԍ�</param>
	/// <returns>�����W</returns>
	Vec2 GetRange(int buttonNum);

private:

	// �֐��|�C���^
	using _UpdateFunc_t = void(MenuManager::*)();
	using _DrawFunc_t = void (MenuManager::*)() const;

	// �A�b�v�f�[�g�֐��A�h���[�֐�
	_UpdateFunc_t _updateFunc = nullptr;
	_DrawFunc_t _drawFunc = nullptr;

	void NormalUpdate();

	void NormalDraw() const;

	void SlideInUpdate();

	void SlideOutUpdate();

	void FadeOutUpdate();

	void FadeOutDraw() const;

	void EndUpdate();

	void EndDraw() const;

	// ���j���[�̊�Չ摜
	int _menuBordHandle;

	// �ڂ����摜�n���h��
	int _backHandle;

	// ��Ղ̕\�����W
	Vec2 _bordPos;

	// �I���w�̃|�C���^
	std::shared_ptr<SelectFinger> _pFinger;

	// �I���{�^��
	std::shared_ptr<MenuButton> _pButton[5];

	// �{�^���R���W�����}�l�[�W���[�|�C���^
	std::shared_ptr<MenuCollisionManager> _pCollisionManager;

	// �X���C�h�C���p�̗]��
	int _margin;

	// �t�F�[�h�p�̃t���[���J�E���^
	int _frame;

	// ���ʒ��߉摜�n���h���z��
	int _volumeSEGraph[4];
	int _volumeBGMGraph[4];
};


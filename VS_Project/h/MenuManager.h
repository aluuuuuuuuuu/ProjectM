#pragma once
#include <memory>
#include "Vec2.h"

#define BATU_BUTTON 0
#define MANUAL_BUTTON 1
#define SE_BUTTON 2
#define BGM_BUTTON 3
#define END_BUTTON 4

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


private:

	// ���j���[�̊�Չ摜
	int _menuBordHandle;

	// ��Ղ̕\�����W
	Vec2 _bordPos;

	// �I���w�̃|�C���^
	std::shared_ptr<SelectFinger> _pFinger;

	// �I���{�^��
	std::shared_ptr<MenuButton> _pButton[5];
};


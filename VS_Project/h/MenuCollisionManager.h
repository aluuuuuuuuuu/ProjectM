#pragma once
#include <memory>
#include "Vec2.h"

class MenuManager;
class MenuCollisionManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mane">���j���[�}�l�[�W���[�̃|�C���^</param>
	MenuCollisionManager(MenuManager& mane);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MenuCollisionManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="fingPos">�w�̍��W</param>
	/// <returns>�������Ă����ꍇ�̓{�^���̒萔��Ԃ��������Ă��Ȃ�������-1</returns>
	int Collision(Vec2 fingPos);
	
private:

	MenuManager& _manager;
};


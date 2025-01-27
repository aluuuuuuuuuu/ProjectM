#pragma once
#include "Vec2.h"

class NumSelectButton
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	NumSelectButton();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~NumSelectButton();

	/// <summary>
	/// �X�V����
	/// </summary>
	void UpdatePl();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �I��l�����擾
	/// </summary>
	/// <returns>�I��l��</returns>
	int GetSelectNum() const;

private:

	// �l���I���{�^���摜
	int _numHandle[4];

	// �Q�[���I���{�^��
	int _gameEndHandle;

	// �I����
	int _arrowHandle;

	// ���\�����W
	Vec2 _arrowPos;

	// �I��l��
	int _selectNum;
};


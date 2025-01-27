#pragma once
#include "Vec2.h"

class MenuButton
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�\�����S���W</param>
	/// <param name="range">�����蔻��͈�</param>
	/// <param name="handle">�摜�n���h��</param>
	/// <param name="type">���g�̃{�^���̎��</param>
	MenuButton(Vec2 pos, Vec2 range, int handle,int type);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MenuButton();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="margin">�]��</param>
	void Draw(int margin) const;

	/// <summary>
	/// �����蔻��͈͂��擾����
	/// </summary>
	/// <returns>�͈�</returns>
	Vec2 GetRange() const;

	/// <summary>
	/// ���W���擾����
	/// </summary>
	/// <returns>���W</returns>
	Vec2 GetPos() const;

	/// <summary>
	/// ��ނ��擾����
	/// </summary>
	/// <returns>���</returns>
	int GetType() const;

	/// <summary>
	/// �摜�������ւ���
	/// </summary>
	/// <param name="handle">�����ւ���摜�n���h��</param>
	void ChangeImage(int handle);

private:

	// �摜�n���h��
	int _graphHandle;

	// �\�����S���W
	Vec2 _pos;

	// �����蔻��͈�
	Vec2 _range;

	// ���g�̎��1
	int _type;
};


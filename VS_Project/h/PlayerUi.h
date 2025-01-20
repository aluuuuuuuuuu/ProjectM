#pragma once
#include "Vec2.h"

class PlayerUi
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playerNum">�v���C���[�̑���</param>
	PlayerUi(int playerNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerUi();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="center">�`��̒��S���W</param>
	void Draw(Vec2 center) const;
private:

	/// <summary>
	/// �ʏ�e�摜�n���h��
	/// </summary>
	int _normalBulletHandle;

	/// <summary>
	/// �����e�摜�n���h��
	/// </summary>
	int _bombBulletHandle;

	/// <summary>
	/// �O���b�v���e�摜�n���h��
	/// </summary>
	int _grappleBulletHandle;

	/// <summary>
	/// ���e�B�N���摜�n���h��
	/// </summary>
	int _reticleHandle;

	/// <summary>
	/// ��ʒ��S����̕`��]��
	/// </summary>
	Vec2 _drawMargin;

	/// <summary>
	/// �A�C�R�����m�̗]��
	/// </summary>
	int _margin;

	/// <summary>
	/// �摜�̊g�嗦
	/// </summary>
	double _exRate;

};


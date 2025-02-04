#pragma once
#include "Vec2.h"
#include "PlayerManager.h"

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
	void Draw(Vec2 center, BulletData data) const;
private:

	// �ʏ�e�摜�n���h��
	int _normalBulletHandle;

	// �����e�摜�n���h��
	int _bombBulletHandle;

	// �O���b�v���e�摜�n���h��
	int _grappleBulletHandle;

	// ���e�B�N���摜�n���h��
	int _reticleHandle;

	// �A�C�R���t���[���摜�n���h��
	int _frameHandle;

	// ��ʒ��S����̕`��]��
	Vec2 _drawMargin;

	// �A�C�R�����m�̗]��
	int _margin;

	// �摜�̊g�嗦
	double _exRate;

	// �t���[���̕`����W
	Vec2 _framePos;

	// �t���[���J�E���^
	float _frame;

};


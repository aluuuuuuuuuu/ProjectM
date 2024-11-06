#pragma once
#include "Vec2.h"
#include "Vec3.h"

class SelectFinger
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="padNum">�p�b�h�i���o�[</param>
	SelectFinger(int padNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SelectFinger();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// ���t���[����A�{�^���������ꂽ���ǂ���
	/// </summary>
	/// <returns>������Ă�����true</returns>
	bool IsPushButton() const;

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>�񎟌����W</returns>
	Vec2 GetPos() const;
private:

	// �p�b�h�i���o�[
	int _padNum;

	// �ő�v���C���[�����̎w�摜�n���h��
	int _fingerHandle[4];

	// �\�����W
	Vec2 _pos;

	// ����{�^���t���O
	bool _pushButtonFlag;
};


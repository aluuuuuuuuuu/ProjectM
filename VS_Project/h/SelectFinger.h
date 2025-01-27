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
	/// ���t���[���ł����ꂩ�̃{�^���������ꂽ���ǂ���
	/// </summary>
	/// <param name="button">�{�^���萔</param>
	/// <returns>������Ă�����true</returns>
	bool IsPushButton(int button) const;

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>�񎟌����W</returns>
	Vec2 GetPos() const;

	/// <summary>
	/// �p�b�h�i���o�[��Ԃ�
	/// </summary>
	/// <returns>�p�b�h�i���o�[</returns>
	int GetPadNum() const;

	/// <summary>
	/// �I���t���O��ύX����
	/// </summary>
	/// <param name="flag">�I���������ǂ���</param>
	void SetSelectFlag(bool flag);

	/// <summary>
	/// �I�����Ă��邩�ǂ����Ԃ�
	/// </summary>
	/// <returns>�I�����Ă�����true</returns>
	bool IsSelected()const;

	/// <summary>
	/// �I������L�������Z�b�g����
	/// </summary>
	/// <param name="charaNum">�I������L�����̃i���o�[</param>
	void SetSelectChara(int charaNum);

	/// <summary>
	/// �I�������L�����i���o�[��Ԃ�
	/// </summary>
	/// <returns>�L�����i���o�[</returns>
	int GetSelectChara()const;

private:

	// �p�b�h�i���o�[
	int _padNum;

	// �ő�v���C���[�����̎w�摜�n���h��
	int _fingerHandle;

	// �\�����W
	Vec2 _pos;

	// �I�������t���O
	bool _selectFlag;

	// �ǂ̃L�����N�^�[��I��������
	int _chara;
};


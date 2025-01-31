#pragma once


class ResultUi
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="time">���j�^�C��</param>
	ResultUi(int time);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ResultUi();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:

	// ���U���g���S�摜�n���h��
	int _resultLogoHandle;

	// �Ԑ��摜�n���h��
	int _redLineHandle;

	// ���j�^�C�������摜�n���h��
	int _timeStringHandle;

	// �����N�g�摜�n���h��
	int _rankFrame;

	// �����N�摜�n���h��
	int _rankHandle;

	// �{�^�������摜�n���h��
	int _guide;
};


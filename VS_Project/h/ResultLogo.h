#pragma once

class ResultLogo
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ResultLogo();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ResultLogo();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:

	// ���S�摜�n���h��
	int _logoHandle;
};


#pragma once

class SelectUI
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SelectUI();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	~SelectUI();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
	
private:
	// �t�@�C�^�[��I�ו��摜�n���h��
	int _selectFighterHandle;

	// �߂�摜
	int _returnHandle;
};


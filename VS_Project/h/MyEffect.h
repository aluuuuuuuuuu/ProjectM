#pragma once
#include "Vec3.h"

class MyEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="effect">�G�t�F�N�g�L�[</param>
	/// <param name="pos">�����ʒu</param>
	MyEffect(int effect, Vec3 pos);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MyEffect();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="pos">���W</param>
	void Update(Vec3 pos);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �G�t�F�N�g���~����
	/// </summary>
	void StopEffect();


private:

	// �v���C�n���h��
	int _playHandle;
};


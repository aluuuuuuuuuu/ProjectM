#pragma once
#include "Components.h"

class Wedgeworm:
	public Transform,
	public Model,
	public Animation
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="num">�i���o�[</param>
	Wedgeworm(int num);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Wedgeworm();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:


};


#pragma once
#include "Components.h"

class SkyDome :
	public Transform,
	public Model
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SkyDome();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SkyDome();

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


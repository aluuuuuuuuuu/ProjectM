#pragma once
#include "Components.h"

class TitlePlayer:
	public Transform,
	public Model,
	public Animation
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���E�ǂ��炩</param>
	/// <param name="num">�v���C���[�i��</param>
	TitlePlayer(int pos,int num);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitlePlayer();

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


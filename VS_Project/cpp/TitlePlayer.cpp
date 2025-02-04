#include "TitlePlayer.h"
#include "DxLib.h"

TitlePlayer::TitlePlayer(int pos, int num)
{
	// �g��̐ݒ�
	Scale = Vec3{ 0.05f,0.05f,0.05f };

	// ��]�̐ݒ�
	Angle = Vec3{ 0.0f,1.5708f,0.0f };

	// �v���C���[�i���ɍ��킹�ăL���������[�h����
	switch (num)
	{
	case 0:
		InitModel(MV1LoadModel("data/model/DancePlayer1.mv1"));
		break;
	case 1:
		InitModel(MV1LoadModel("data/model/DancePlayer2.mv1"));
		break;
	case 2:
		InitModel(MV1LoadModel("data/model/DancePlayer3.mv1"));
		break;
	case 3:
		InitModel(MV1LoadModel("data/model/DancePlayer4.mv1"));
		break;
	default:
		break;
	}

	// ���W�̐ݒ�
	switch (pos)
	{
	case 0:	// �E
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 1:	// ��
		Position = Vec3{ 120.0f, 240.0f, -15.0f };
		break;
	default:
		break;
	}

	// �����q�̗�O����
	//if (num == 2) {
		// �A�j���[�V�����̏�������
		//InitAnimation(_modelHandle, 0, 0.5f);
		//ChangeAnimation(_modelHandle, 0, true, 0.1f);
	//}
	//else {
		// �A�j���[�V�����̏�������
	InitAnimation(_modelHandle, 0, 0.5f);
	ChangeAnimation(_modelHandle, 1, true, 0.1f);
	//}

	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Update()
{
	// �A�j���[�V�����̍X�V
	UpdateAnimation(_modelHandle, 0.5f);

	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

void TitlePlayer::Draw() const
{
	DrawModel();
}

#include "CreditCharacter.h"
#include "DxLib.h"

CreditCharacter::CreditCharacter(int num):
	_num(num)
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

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 1:
		InitModel(MV1LoadModel("data/model/DancePlayer2.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 240.0f,  -15.0f };
		break;
	case 2:
		InitModel(MV1LoadModel("data/model/DancePlayer3.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 3:
		InitModel(MV1LoadModel("data/model/DancePlayer4.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 240.0f, -15.0f };
		break;
	default:
		break;
	}

	InitAnimation(_modelHandle, 0, 0.5f);
	ChangeAnimation(_modelHandle, 1, true, 0.1f);


	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

CreditCharacter::~CreditCharacter()
{
}

void CreditCharacter::Update()
{
	// �A�j���[�V�����̍X�V
	UpdateAnimation(_modelHandle, 0.5f);

	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

void CreditCharacter::Draw() const
{
	DrawModel();
}

void CreditCharacter::PosSet()
{
	switch (_num)
	{
	case 0:

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 1:

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 250.0f,  -15.0f };
		break;
	case 2:

		// ���W�̐ݒ�
		Position = Vec3{ 120.0f, 250.0f, 10.0f };
		break;
	case 3:
		break;
	default:
		break;
	}
}

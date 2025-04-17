#include "CreditCharacter.h"
#include "DxLib.h"

CreditCharacter::CreditCharacter(int num) :
	_num(num)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/CreditCharactor.csv");

	// �g��̐ݒ�
	Scale = GetConstantFloat("CHARACTOR_SCALE");

	// ��]�̐ݒ�
	Angle = Vec3{ GetConstantFloat("CHARACTOR_ANGLE_X"),
		GetConstantFloat("CHARACTOR_ANGLE_Y"),
		GetConstantFloat("CHARACTOR_ANGLE_Z") };

	// �v���C���[�i���ɍ��킹�ăL���������[�h����
	switch (num)
	{
	case 0:
		InitModel(MV1LoadModel("data/model/DancePlayer1.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y"), GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	case 1:
		InitModel(MV1LoadModel("data/model/DancePlayer2.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y"),  -GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	case 2:
		InitModel(MV1LoadModel("data/model/DancePlayer3.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y"), GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	case 3:
		InitModel(MV1LoadModel("data/model/DancePlayer4.mv1"));

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y"), -GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	default:
		break;
	}

	InitAnimation(_modelHandle, GetConstantInt("ANIM_IDLE"), GetConstantFloat("ANIM_BLEND_RATE"));
	ChangeAnimation(_modelHandle, GetConstantInt("ANIM_DANCE"), true, GetConstantFloat("ANIM_BLEND_RATE"));


	// ���f���̍X�V
	UpdateModel(GetTransformInstance());
}

CreditCharacter::~CreditCharacter()
{
}

void CreditCharacter::Update()
{
	// �A�j���[�V�����̍X�V
	UpdateAnimation(_modelHandle, GetConstantFloat("ANIM_SPEED"));

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
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y"), GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	case 1:

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y") + 10.0f,  -GetConstantFloat("CHARACTOR_POS_Z") };
		break;
	case 2:

		// ���W�̐ݒ�
		Position = Vec3{ GetConstantFloat("CHARACTOR_POS_X"), GetConstantFloat("CHARACTOR_POS_Y") + 10.0f, GetConstantFloat("CHARACTOR_POS_Z") + 5.0f };
		break;
	case 3:
		break;
	default:
		break;
	}
}

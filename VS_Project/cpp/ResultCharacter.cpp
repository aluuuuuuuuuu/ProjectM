#include "ResultCharacter.h"
#include "DxLib.h"

ResultCharacter::ResultCharacter(int plNum)
{
	switch (plNum)
	{
	case 1:

		// �g�����X�t�H�[���̐ݒ�
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// �g�嗦
		Position = Vec3{ -50,-12,0 };	// ���W
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// �p�x

		// ���f���̏�������
		InitModel(MV1LoadModel("data/model/ResultCharacter1.mv1"));

		// �A�j���[�V�����̏�������
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);

		break;

	case 2:

		// �g�����X�t�H�[���̐ݒ�
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// �g�嗦
		Position = Vec3{ -20,-13,5 };	// ���W
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// �p�x

		// ���f���̏�������
		InitModel(MV1LoadModel("data/model/ResultCharacter2.mv1"));

		// �A�j���[�V�����̏�������
		InitAnimation(_modelHandle, 0, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);
		break;

	case 3:

		// �g�����X�t�H�[���̐ݒ�
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// �g�嗦
		Position = Vec3{-10,-13,2 };	// ���W
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// �p�x

		// ���f���̏�������
		InitModel(MV1LoadModel("data/model/ResultCharacter3.mv1"));

		// �A�j���[�V�����̏�������
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 0, false, 0.5f);
		break;

	case 4:

		// �g�����X�t�H�[���̐ݒ�
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// �g�嗦
		Position = Vec3{ -28,-14,3 };	// ���W
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// �p�x

		// ���f���̏�������
		InitModel(MV1LoadModel("data/model/ResultCharacter4.mv1"));

		// �A�j���[�V�����̏�������
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);
		break;
	default:
		break;
	}

	// �J�����̃j�A�t�@�[�̃Z�b�g
	SetCameraNearFar(1.0f, 100.0f);

	// �J�����̍��W�̃Z�b�g
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(-1, 0, 0));

	// ���C�g�̊p�x�̒���
	SetLightDirection(VGet(-1, 0, 0));
}

ResultCharacter::~ResultCharacter()
{
}

void ResultCharacter::Update()
{

	//// �A�j���[�V�������I�����Ă���ꍇ�̏���
	//if (GetEndAnimFlag()) {

	//	// �I�������^�C�~���O���Ƃ�
	//	if (!_flag) {
	//		_maxAnimeFlame = GetAnimeFlame();	// �ő�l��ۑ�
	//		_flag = true;
	//	}

	//	// �A�j���[�V�����̑�����؂�ւ���
	//	if (GetAnimeFlame() == _maxAnimeFlame - 3) {
	//		_animFlag = true;
	//	}
	//	else if(GetAnimeFlame() == _maxAnimeFlame) {
	//		_animFlag = false;
	//	}

	//	// �t���[���̑���
	//	if (_animFlag) {
	//		UpdateAnimationOnce(_modelHandle, 0.1);
	//	}
	//	else {
	//		UpdateAnimationOnce(_modelHandle, -0.1);
	//	}
	//	
	//}
	//else {
	//	UpdateAnimationOnce(_modelHandle, 0.5);
	//}

	UpdateAnimationOnce(_modelHandle, 0.5f);
	// ���f���̍X�V����
	UpdateModel(GetTransformInstance());
}

void ResultCharacter::Draw() const
{
	DrawModel();
}

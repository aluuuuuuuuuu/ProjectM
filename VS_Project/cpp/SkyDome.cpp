#include "SkyDome.h"
#include "DxLib.h"

SkyDome::SkyDome()
{
	// ���f���̏�������
	InitModel(MV1LoadModel("data/model/Skydome.mv1"));

	// �g�嗦�̐ݒ�
	Scale = Vec3{ 0.04f, 0.06f, 0.04f };

	// ���W�̐ݒ�
	Position = Vec3{ 0.0f,-100.0f,0.0f };

	// ��x��̐ݒ�𔽉f������
	UpdateModel(GetTransformInstance());
}

SkyDome::~SkyDome()
{
}

void SkyDome::Update()
{
	// �����Âh�[����y�������ĉ_�������Ă�ӂ��Ɍ�����
	Angle.y += 0.0001f;

	// ���f���̍X�V����
	UpdateModel(GetTransformInstance());
}

void SkyDome::Draw() const
{
	// �`�揈��
	DrawModel();
}
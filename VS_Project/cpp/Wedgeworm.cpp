#include "Wedgeworm.h"
#include "DxLib.h"

Wedgeworm::Wedgeworm(int num,int model):
	_angle(0)
{
	// �������W�̐ݒ�
	_pos = Vec3{ 120.0f,50.0f,120.0f };

	// �i���o�[�ŏ������W��؂�ւ���
	if (num == 0) {
		_angle = 3.14f;
		Angle.y = 0.0f;
	}
	else {
		_angle = 0.0f;
		Angle.y = 3.14f;
	}
	
	// ��]�s��������p�x�ŉ�]�����Ă���
	MATRIX mtx = MGetRotY(_angle);
	_pos = VTransform(_pos.VGet(), mtx);

	// �g��̐ݒ�
	Scale = Vec3{ 0.1f,0.1f,0.1f };

	// ���f���̏�������
	InitModel(MV1DuplicateModel(model));

	// ��ɉ�]����ʂ����
	_angle = 0.005f;

	// ��]�s����쐬����
	_mtx = MGetRotY(_angle);
}

Wedgeworm::~Wedgeworm()
{
}

void Wedgeworm::Update()
{

	// �쐬������]�s������W�ɓK�p����
	_pos = VTransform(_pos.VGet(), _mtx);

	Angle.y += 0.0045f;

	// ���W�A���p�𐳋K������
	Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
	if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);

	// �V�����쐬���č��W�𒲐�����
	Position = Vec3{ _pos.x + 120, _pos.y,_pos.z + 120 };

	// ���f���̍X�V����
	UpdateModel(GetTransformInstance());
}

void Wedgeworm::Draw() const
{
	// ���f���̕`��
	DrawModel();
}

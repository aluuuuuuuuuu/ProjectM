#include "Wedgeworm.h"

Wedgeworm::Wedgeworm(int num)
{
	if (num == 0) {
		Position = Vec3{ 0.0f,30.f,0.0f };
	}
	else {
		Position = Vec3{ 60.0f,30.f,60.0f };
	}
}

Wedgeworm::~Wedgeworm()
{
}

void Wedgeworm::Update()
{
	// ���f���̍X�V����
	UpdateModel(GetTransformInstance());
}

void Wedgeworm::Draw() const
{
	// ���f���̕`��
	DrawModel();
}

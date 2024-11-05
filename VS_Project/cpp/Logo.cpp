#include "Logo.h"
#include "DxLib.h"
#include "SceneTitle.h"

Logo::Logo(SceneTitle& scene)
{
	// �摜�̃��[�h
	_logo = LoadGraph("data/image/TitleLogo.png");

	// �\���ʒu�̐ݒ�
	_dispPos = Vec2{ scene.GetConstantInt("LOGO_POS_X"),scene.GetConstantInt("LOGO_POS_Y") };
}

Logo::~Logo()
{
	DeleteGraph(_logo);
}

void Logo::Draw() const
{
	// ���S�̕`��
	DrawRotaGraph(_dispPos.intX(), _dispPos.intY(), 1.0f, 0.0f, _logo, true);
}

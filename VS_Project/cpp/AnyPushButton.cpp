#include "AnyPushButton.h"
#include "DxLib.h"
#include "SceneTitle.h"

AnyPushButton::AnyPushButton(SceneTitle& scene):
	_frame(0)
{
	// �摜�̃��[�h
	_textHandle = LoadGraph("data/image/PressAnyButton.png");
	
	// �\���ʒu�̐ݒ�
	_dispPos = Vec2{ scene.GetConstantInt("TEXT_POS_X"),scene.GetConstantInt("TEXT_POS_Y") };
}

AnyPushButton::~AnyPushButton()
{
	DeleteGraph(_textHandle);
}

void AnyPushButton::Update()
{
	// �X�^�[�g�w����_�ł�����
	if (_frame == 120) {
		_frame++;
	}
	else if (_frame == 1) {
		_frame--;
	}
	else if (_frame % 2 == 0) {
		_frame += 2;
	}
	else {
		_frame -= 2;
	}
}

void AnyPushButton::Draw() const
{
	// �t�F�[�h���Ȃ���`��
	int alpha = static_cast<int>(255 * ((float)_frame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// �摜�̕`��
	DrawRotaGraph(_dispPos.intX(), _dispPos.intY(), 1.0f, 0.0f, _textHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

#include "Crown.h"
#include "DxLib.h"
#include "SceneTitle.h"

Crown::Crown(SceneTitle& scene) :
	_flame1(0),
	_flame2(0),
	_flame1Flag(true),
	_blinkingFlag(false)
{
	// �\���ʒu�̐ݒ�
	_dispPos = Vec2{ scene.GetConstantInt("CROWN_POS_X"),scene.GetConstantInt("CROWN_POS_Y") };

	// �摜�̃��[�h
	{
		_crownHandle = LoadGraph("data/image/Crown.png");	// �����摜�̃��[�h
		_crownParticleHandle1 = LoadGraph("data/image/CrownParticle1.png");	// �����p�[�e�B�N��1�摜�̃��[�h
		_crownParticleHandle2 = LoadGraph("data/image/CrownParticle2.png");	// �����p�[�e�B�N��2�摜�̃��[�h
		_crownParticleHandle3 = LoadGraph("data/image/CrownParticle3.png");	// �����p�[�e�B�N��3�摜�̃��[�h
	}

	// �\������p�[�e�B�N���̏����ݒ�
	_crownParticle = _crownParticleHandle1;
}

Crown::~Crown()
{
	DeleteGraph(_crownHandle);
	DeleteGraph(_crownParticleHandle1);
	DeleteGraph(_crownParticleHandle2);
	DeleteGraph(_crownParticleHandle3);
}

void Crown::Update()
{
	// �����S�̂�_�ł�����
	if (!_flame1Flag) {
		if (_flame1 <= 0) {
			_flame1Flag = true;
			_blinkingFlag = false;
			_flame2 = 0;
		}
		else {
			_flame1 -= 2;
		}
	}
	else {
		if (_flame1 >= 120) {
			_blinkingFlag = true;
		}
		else {
			_flame1 += 2;
		}
	}

	// �p�[�e�B�N���̓_��
	if (_blinkingFlag) {
		_flame2++;
		if (_flame2 <= 30) {
			_crownParticle = _crownParticleHandle1;
		}
		else if (_flame2 <= 60) {
			_crownParticle = _crownParticleHandle2;
		}
		else if (_flame2 <= 90) {
			_crownParticle = _crownParticleHandle3;
		}
		else {
			_flame1Flag = false;
		}
	}
}

void Crown::Draw()
{
	int alpha = static_cast<int>(255 * ((float)_flame1 / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// �����摜�̕`��
	DrawRotaGraph(_dispPos.intX(), _dispPos.intY(), 0.2f, -0.5f, _crownHandle, true);

	// �����p�[�e�B�N���摜�̕`��
	if (_blinkingFlag) {
		DrawRotaGraph(_dispPos.intX(), _dispPos.intY(), 0.2f, -0.5f, _crownParticle, true);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

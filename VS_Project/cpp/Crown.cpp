#include "Crown.h"
#include "DxLib.h"

Crown::Crown() :
	_flame1(0),
	_flame2(0),
	_flame1Flag(true),
	_blinkingFlag(false)
{
	// �萔�̓ǂݍ���
	ReadCSV("data/constant/Crown.csv");

	// �����摜�̃��[�h
	_crownHandle = LoadGraph("data/image/Crown.png");

	// �����p�[�e�B�N���摜�̃��[�h
	_crownParticleHandle1 = LoadGraph("data/image/CrownParticle1.png");
	_crownParticleHandle2 = LoadGraph("data/image/CrownParticle2.png");
	_crownParticleHandle3 = LoadGraph("data/image/CrownParticle3.png");
}

Crown::~Crown()
{
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
	int alpha = (int)(255 * ((float)_flame1 / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// �����摜�̕`��
	DrawRotaGraph(GetConstantInt("DRAW_POS_X"), GetConstantInt("DRAW_POS_Y"), 0.2f, -0.5f, _crownHandle, true);

	// �����p�[�e�B�N���摜�̕`��
	if (_blinkingFlag) {
		DrawRotaGraph(GetConstantInt("DRAW_POS_X"), GetConstantInt("DRAW_POS_Y"), 0.2f, -0.5f, _crownParticle, true);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

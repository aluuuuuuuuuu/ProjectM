#pragma once
#include "Components.h"

class ResultCharacter :
	public Model,
	public Animation,
	public Transform
{
public:
	ResultCharacter(int plNum);
	virtual ~ResultCharacter();

	void Update();

	void Draw() const;

private:

	//// �A�j���[�V�������I�������^�C�~���O���Ƃ邽�߂̃t���O
	//bool _flag;

	//// ���o�A�j���[�V�����̍ő�t���[��������
	//int _maxAnimeFrame;

	//// �A�j���[�V�����̃t���[���𑝂₷�����炷���𔻒f����t���O
	//bool _animFlag;

};


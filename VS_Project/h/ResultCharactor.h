#pragma once
#include "Components.h"

class ResultCharactor :
	public Model,
	public Animation,
	public Transform
{
public:
	ResultCharactor(int plNum);
	virtual ~ResultCharactor();

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


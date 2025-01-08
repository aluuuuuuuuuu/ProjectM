#pragma once
#include "Vec2.h"

#define NUM_0 0
#define NUM_1 1
#define NUM_2 2
#define NUM_3 3
#define NUM_4 4
#define NUM_5 5
#define NUM_6 6
#define NUM_7 7
#define NUM_8 8
#define NUM_9 9
#define NUM_DOT 10


class NumUtility
{
public:
	NumUtility(float size ,Vec2 pos, int num);

	NumUtility(float size, Vec2 pos);

	virtual ~NumUtility();

	void Update(int time);

	void Draw() const;

private:

	// �����摜�n���h��
	int _numHandle[11];

	// �\������摜�̃n���h���������Ă����z��
	int _drawNumHandle[6];

	// �����\�����鍶��̍��W
	Vec2 _drawPos;

	float _size;
};


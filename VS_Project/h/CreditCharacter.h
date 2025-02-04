#pragma once
#include "Components.h"

class CreditCharacter:
	public Transform,
	public Model,
	public Animation
{
public:

	CreditCharacter(int num);

	~CreditCharacter();

	void Update();

	void Draw() const;

	void PosSet();
private:
	int _num;
};


#pragma once
#include "Vec2.h"

class CharactorCard
{
public:
	CharactorCard(int charNum);
	virtual ~CharactorCard();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:

	// �J�[�h�摜�n���h��
	int _cardHandle;

	int _cardSelectedRed;
	int _cardSelectedBlue;
	int _cardSelectedGreen;
	int _cardSelectedYellow;

	// �J�[�h�`����W
	Vec2 _pos;
};


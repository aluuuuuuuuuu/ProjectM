#include "CharacterCard.h"
#include "DxLib.h"
#include "SceneSelect.h"
#include "PlayerManager.h"

CharacterCard::CharacterCard(int charNum) :
	_cardHandle(0),
	_characterNum(charNum)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/CharacterCard.csv");

	// �L�����摜�̃��[�h
	switch (charNum)
	{
	case 0:
		_cardHandle = LoadGraph("data/image/Card1.png");
		_pos = Vec2{ GetConstantInt("CARD1_POS_X"),GetConstantInt("CARD1_POS_Y") };
		break;
	case 1:
		_cardHandle = LoadGraph("data/image/Card2.png");
		_pos = Vec2{ GetConstantInt("CARD2_POS_X"),GetConstantInt("CARD2_POS_Y") };
		break;
	case 2:
		_cardHandle = LoadGraph("data/image/Card3.png");
		_pos = Vec2{ GetConstantInt("CARD3_POS_X"),GetConstantInt("CARD3_POS_Y") };
		break;
	case 3:
		_cardHandle = LoadGraph("data/image/Card4.png");
		_pos = Vec2{ GetConstantInt("CARD4_POS_X"),GetConstantInt("CARD4_POS_Y") };
		break;
	default:
		break;
	}

	// �I����摜�̃��[�h
	{
		_cardSelectHandle[PLAYER_ONE] = LoadGraph("data/image/CardSelectedRed.png");
		_cardSelectHandle[PLAYER_TWO] = LoadGraph("data/image/CardSelectedBlue.png");
		_cardSelectHandle[PLAYER_THREE] = LoadGraph("data/image/CardSelectedGreen.png");
		_cardSelectHandle[PLAYER_FORE] = LoadGraph("data/image/CardSelectedYellow.png");
	}

	// �I���t���O�̏�����
	for (auto& flag : _selectFlag) {
		flag = false;
	}
}

CharacterCard::~CharacterCard()
{
	// �摜�̃f���[�g
	DeleteGraph(_cardHandle);
	for (auto& handle : _cardSelectHandle) {
		DeleteGraph(handle);
	}
}

void CharacterCard::Update(std::shared_ptr<SelectFinger>& fing)
{
}

void CharacterCard::Draw() const
{
	// �K�[�h�̕`��
	DrawGraph(_pos.intX(), _pos.intY(), _cardHandle, true);

	// �t���O�ɉ����đI����̉摜��`�悷��
	for (int i = 0; i <= PLAYER_FORE; i++) {
		if (_selectFlag[i]) {
			DrawGraph(_pos.intX() + 10, _pos.intY() + 10, _cardSelectHandle[i], true);
			break;
		}
	}
}

void CharacterCard::SelectCharacter(int plNum)
{
	_selectFlag[plNum] = true;
}

void CharacterCard::RejectCharacter(int plNum)
{
	_selectFlag[plNum] = false;
}

bool CharacterCard::GetSelectFlag()
{
	for (auto& flag : _selectFlag) {
		if (flag) return true;
	}
	return false;
}

bool CharacterCard::GetSelectFlag(int plNum)
{
	return _selectFlag[plNum];
}

Vec2 CharacterCard::GetPos() const
{
	return _pos;
}

int CharacterCard::GetCharacterNum() const
{
	return _characterNum;
}

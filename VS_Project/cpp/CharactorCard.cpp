#include "CharactorCard.h"
#include "DxLib.h"
#include "SceneSelect.h"
#include "PlayerManager.h"

CharactorCard::CharactorCard(int charNum) :
	_cardHandle(0),
	_charactorNum(charNum)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/CharactorCard.csv");

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

CharactorCard::~CharactorCard()
{
	// �摜�̃f���[�g
	DeleteGraph(_cardHandle);
	for (auto& handle : _cardSelectHandle) {
		DeleteGraph(handle);
	}
}

void CharactorCard::Update(std::shared_ptr<SelectFinger>& fing)
{
}

void CharactorCard::Draw() const
{

	// �K�[�h�̕`��
	DrawGraph(_pos.intX(), _pos.intY(), _cardHandle, true);

	// �t���O�ɉ����đI����̉摜��`�悷��
	for (int i = 0; i < PLAYER_FORE; i++) {
		if (_selectFlag[i]) {
			DrawGraph(_pos.intX() + 10, _pos.intY() + 10, _cardSelectHandle[i], true);
			break;
		}
	}
}

void CharactorCard::SelectCharactor(int plNum)
{
	_selectFlag[plNum] = true;
}

void CharactorCard::RejectCharactor(int plNum)
{
	_selectFlag[plNum] = false;
}

bool CharactorCard::GetSelectFlag()
{
	for (auto& flag : _selectFlag) {
		if (flag) return true;
	}
	return false;
}

bool CharactorCard::GetSelectFlag(int plNum)
{
	return _selectFlag[plNum];
}

Vec2 CharactorCard::GetPos() const
{
	return _pos;
}

int CharactorCard::GetCharactorNum() const
{
	return _charactorNum;
}

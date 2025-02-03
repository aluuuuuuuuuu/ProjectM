#include "NumSelectButton.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerManager.h"
#include "SoundManager.h"

NumSelectButton::NumSelectButton():
	_selectNum(0),
	_message(false)
{
	// �l���I���̉摜�̃��[�h
	_numHandle[PLAYER_ONE] = LoadGraph("data/image/1play.png");
	_numHandle[PLAYER_TWO] = LoadGraph("data/image/2play.png");
	_numHandle[PLAYER_THREE] = LoadGraph("data/image/3play.png");
	_numHandle[PLAYER_FORE] = LoadGraph("data/image/4play.png");

	// �I����̃��[�h
	_arrowHandle = LoadGraph("data/image/arrow.png");

	// ���b�Z�[�W�摜�̃��[�h
	_messageHandle = LoadGraph("data/image/message.png");

	_arrowPos = Vec2{ 690,875 };
}

NumSelectButton::~NumSelectButton()
{
	// �摜�̍폜
	for (auto& han : _numHandle) {
		DeleteGraph(han);
	}

	DeleteGraph(_gameEndHandle);
	DeleteGraph(_messageHandle);

}

void NumSelectButton::Update()
{
	// �C���v�b�g�C���X�^���X���擾
	auto& input = Input::GetInstance();

	// �E���͂����ꂽ�Ƃ��̓���
	if (input.IsTrigger(INPUT_RIGHT, INPUT_PAD_1)) {

		// �I������炷
		SoundManager::GetInstance().RingSE(SE_NUM_SELECT);

		switch (_arrowPos.intX())
		{
		case 690:
			_arrowPos.x = static_cast<int>(890);
			_selectNum = PLAYER_TWO;
			break;
		case 890:
			_arrowPos.x = static_cast<int>(1090);
			_selectNum = PLAYER_THREE;
			break;
		case 1090:
			_arrowPos.x = static_cast<int>(1290);
			_selectNum = PLAYER_FORE;
			break;
		case 1290:
			_arrowPos.x = static_cast<int>(690);
			_selectNum = PLAYER_ONE;
			break;
		default:
			break;
		}
	}

	// �����͂����ꂽ�Ƃ��̓���
	if (input.IsTrigger(INPUT_LEFT, INPUT_PAD_1)) {

		// �I������炷
		SoundManager::GetInstance().RingSE(SE_NUM_SELECT);

		switch (_arrowPos.intX())
		{
		case 690:
			_arrowPos.x = static_cast<int>(1290);
			_selectNum = PLAYER_FORE;
			break;
		case 890:
			_arrowPos.x = static_cast<int>(690);
			_selectNum = PLAYER_ONE;
			break;
		case 1090:
			_arrowPos.x = static_cast<int>(890);
			_selectNum = PLAYER_TWO;
			break;
		case 1290:
			_arrowPos.x = static_cast<int>(1090);
			_selectNum = PLAYER_THREE;
			break;
		default:
			break;
		}
	}
}

void NumSelectButton::Draw() const
{
	// ���̕`��
	DrawRotaGraph(_arrowPos.intX(), _arrowPos.intY(), 1, 0, _arrowHandle, true);

	// �l���̕`��
	DrawRotaGraph(690, 950, 1, 0, _numHandle[0], true);
	DrawRotaGraph(890, 950, 1, 0, _numHandle[1], true);
	DrawRotaGraph(1090, 950, 1, 0, _numHandle[2], true);
	DrawRotaGraph(1290, 950, 1, 0, _numHandle[3], true);

	if (_message) {
		DrawGraph(30, 170, _messageHandle, true);
	}
}

int NumSelectButton::GetSelectNum() const
{
	return _selectNum;
}

void NumSelectButton::SetMessage()
{
	_message = true;
}

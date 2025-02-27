#include "SelectModeUi.h"
#include "DxLib.h"
#include "Input.h"
#include "MyMath.h"
#include "Vec3.h"
#include "SoundManager.h"

SelectModeUi::SelectModeUi() :
	_selectButtonNum(SOLO_MODE),
	_circleAngle(0.0),
	_frame(0),
	_input(false),
	_circleScale(1.0),
	_changeFrag(false)
{
	// �摜�̃��[�h
	{
		// �����̉~
		_circleHandle[SOLO_MODE] = LoadGraph("data/image/CenterCircle1.png");
		_circleHandle[MULTI_MODE] = LoadGraph("data/image/CenterCircle2.png");
		_circleHandle[TUTORIAL_MODE] = LoadGraph("data/image/CenterCircle3.png");
		_circleHandle[OPTION_MODE] = LoadGraph("data/image/CenterCircle4.png");

		_circleLogoHandle = LoadGraph("data/image/CenterCircleLogo.png");

		_centerArrowHandle[SOLO_MODE] = LoadGraph("data/image/CenterArrow1.png");
		_centerArrowHandle[MULTI_MODE] = LoadGraph("data/image/CenterArrow2.png");
		_centerArrowHandle[TUTORIAL_MODE] = LoadGraph("data/image/CenterArrow3.png");
		_centerArrowHandle[OPTION_MODE] = LoadGraph("data/image/CenterArrow4.png");

		// �{�^��
		_buttonHandle[SOLO_MODE] = LoadGraph("data/image/Button1.png");
		_buttonHandle[MULTI_MODE] = LoadGraph("data/image/Button2.png");
		_buttonHandle[TUTORIAL_MODE] = LoadGraph("data/image/Button3.png");
		_buttonHandle[OPTION_MODE] = LoadGraph("data/image/Button4.png");

		// �n�C���C�g
		_highlightHandle[SOLO_MODE] = LoadGraph("data/image/Highlight1.png");
		_highlightHandle[MULTI_MODE] = LoadGraph("data/image/Highlight2.png");
		_highlightHandle[TUTORIAL_MODE] = LoadGraph("data/image/Highlight3.png");
		_highlightHandle[OPTION_MODE] = LoadGraph("data/image/Highlight4.png");

		// ���b�Z�[�W
		_messageHandle[SOLO_MODE] = LoadGraph("data/image/Message01.png");
		_messageHandle[MULTI_MODE] = LoadGraph("data/image/Message02.png");
		_messageHandle[TUTORIAL_MODE] = LoadGraph("data/image/Message03.png");
		_messageHandle[OPTION_MODE] = LoadGraph("data/image/Message04.png");

		// �]��
		_marginHandle[SOLO_MODE] = LoadGraph("data/image/Margin1.png");
		_marginHandle[MULTI_MODE] = LoadGraph("data/image/Margin2.png");
		_marginHandle[TUTORIAL_MODE] = LoadGraph("data/image/Margin3.png");
		_marginHandle[OPTION_MODE] = LoadGraph("data/image/Margin4.png");
	}

	// �{�^���摜�̍��W��ݒ肷��
	_buttonPos[SOLO_MODE] = Vec2{ 202, 118 };
	_buttonPos[MULTI_MODE] = Vec2{ 976, 118 };
	_buttonPos[TUTORIAL_MODE] = Vec2{ 202, 631 };
	_buttonPos[OPTION_MODE] = Vec2{ 976, 631 };

	// �����̉~�̍��W
	_circlePos = Vec2{ 960,620 };

	// �ŏ��ɑI������Ă��鍀�ڂ̐ݒ�
	_selectButtonNum = TUTORIAL_MODE;
	_oldSelectButtonNum = _selectButtonNum;
}

SelectModeUi::~SelectModeUi()
{
	// �摜�̍폜
	for (auto& handle : _buttonHandle) {
		DeleteGraph(handle);
	}
	for (auto& handle : _messageHandle) {
		DeleteGraph(handle);
	}
}

void SelectModeUi::Update()
{
	// �I������Ă���{�^���ɂ���Ċp�x��ς���
	switch (_selectButtonNum)
	{
	case SOLO_MODE:
		_circleAngle = GetRadian(SOLO_ANGLE);
		break;
	case MULTI_MODE:
		_circleAngle = GetRadian(MULTI_ANGLE);
		break;
	case TUTORIAL_MODE:
		_circleAngle = GetRadian(TUTORIAL_ANGLE);
		break;
	case OPTION_MODE:
		_circleAngle = GetRadian(OPTION_ANGLE);
		break;
	default:
		break;
	}

	// �X�e�B�b�N�őI����؂�ւ���
	Vec3 stick = Input::GetInstance().GetStickVector(INPUT_LEFT_STICK, INPUT_PAD_1);

	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > 10000.0f) {
		if (stick.x < 0.0f && stick.z > 0.0f) {
			_selectButtonNum = SOLO_MODE;
		}
		else if (stick.x > 0.0f && stick.z > 0.0f) {
			_selectButtonNum = MULTI_MODE;
		}
		else if (stick.x < 0.0f && stick.z < 0.0f) {
			_selectButtonNum = TUTORIAL_MODE;
		}
		else if (stick.x > 0.0f && stick.z < 0.0f) {
			_selectButtonNum = OPTION_MODE;
		}

		// �t���[����������
		if (_oldSelectButtonNum != _selectButtonNum) {
			_frame = 0;
			SoundManager::GetInstance().RingSE(SE_NUM_SELECT);
		}

		// �ύX�t���O�𗧂Ă�
		_changeFrag = true;
	}
	_oldSelectButtonNum = _selectButtonNum;

	// �ύX�t���O�������Ă�����t���[�������Z����
	if (_changeFrag) _frame++;

	// ����̃t���[�����𒴂�����
	if (_frame > 30) {
		_changeFrag = false;
	}
	else {
		// �t���[���Ŋg�嗦�̑�����؂�ւ���
		if (_frame < 3) {
			_circleScale = 0.7;
		}
		else {
			_circleScale += 0.05;
			_circleScale = min(1.0, _circleScale);
		}

		// �t���[���̉��Z
		_frame++;
	}
}

void SelectModeUi::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �{�^���̃n�C���C�g�̕`��
	DrawGraph(_buttonPos[_selectButtonNum].intX(), _buttonPos[_selectButtonNum].intY(), _highlightHandle[_selectButtonNum], true);

	// �{�^���̕`��
	for (int i = 0; i < 4; i++) {
		//DrawRotaGraph(_buttonPos[i].intX(), _buttonPos[i].intY(), 1.0f, 0.0, _buttonHandle[i], true);
		DrawGraph(_buttonPos[i].intX(), _buttonPos[i].intY(), _buttonHandle[i], true);
	}

	// �����̉~�̕`��
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), 1.0, 0.0, _marginHandle[_selectButtonNum], true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, _circleAngle, _circleHandle[_selectButtonNum], true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, 0.0, _circleLogoHandle, true);
	DrawRotaGraph(_circlePos.intX(), _circlePos.intY(), _circleScale, _circleAngle, _centerArrowHandle[_selectButtonNum], true);

	// ���̎l�p�̕`��
	DrawBox(0, 986, 1920, 1080, 0x000000, true);

	// ���̃��b�Z�[�W�n���h��
	DrawRotaGraph(960, 1033, 1.0, 0.0, _messageHandle[_selectButtonNum], true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1));
}

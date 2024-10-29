#include "Input.h"
#include <cassert>

void Input::Update()
{
	// �ڑ�����Ă���R���g���[���[�̐����擾����
	_padNum = GetJoypadNum();

	int num = 0x0001;

	// �ȑO�̃X�e�[�g��ۑ�
	for (int i = 0; i < _padNum; i++) {

		// �ȑO�̃X�e�[�g��ۑ�
		m_lastPadState[i] = m_padState[i];

		// ���݂̃X�e�[�g���擾
		GetJoypadXInputState(num,&m_padState[i]);

		num += 0x0001;
	}
}

// �������u��
bool Input::IsTrigger(int input, int padNum) const
{
	assert(padNum < _padNum);

	if (input == INPUT_A) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_A] && m_padState[padNum].Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_B] && m_padState[padNum].Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_X] && m_padState[padNum].Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_Y] && m_padState[padNum].Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_START] && m_padState[padNum].Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_BACK] && m_padState[padNum].Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB] && m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB] && m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (!m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState[padNum].LeftTrigger <= 0 && m_padState[padNum].LeftTrigger >= 1);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState[padNum].RightTrigger <= 0 && m_padState[padNum].RightTrigger >= 1);
	}

	return false;
}

// �����Ă����
bool Input::IsHold(int input, int padNum) const
{
	if (input == INPUT_A) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_A] && m_padState[padNum].Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_B] && m_padState[padNum].Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_X] && m_padState[padNum].Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_Y] && m_padState[padNum].Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT] && m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_START] && m_padState[padNum].Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_BACK] && m_padState[padNum].Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB] && m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB] && m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState[padNum].LeftTrigger >= 1 && m_padState[padNum].LeftTrigger >= 1);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState[padNum].RightTrigger >= 1 && m_padState[padNum].RightTrigger >= 1);
	}
	return false;
}

// �������u��
bool Input::IsRelease(int input, int padNum) const
{
	if (input == INPUT_A) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_A] && !m_padState[padNum].Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_B] && !m_padState[padNum].Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_X] && !m_padState[padNum].Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_Y] && !m_padState[padNum].Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP] && !m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN] && !m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT] && !m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT] && !m_padState[padNum].Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_START] && !m_padState[padNum].Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_BACK] && !m_padState[padNum].Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB] && !m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB] && !m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && !m_padState[padNum].Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (m_lastPadState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !m_padState[padNum].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState[padNum].LeftTrigger >= 1 && m_padState[padNum].LeftTrigger <= 0);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState[padNum].RightTrigger >= 1 && m_padState[padNum].RightTrigger <= 0);
	}
	return false;
}

Vec3 Input::GetStickVector(int input, int padNum) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbLX),0.0f,static_cast<float>(m_padState[padNum].ThumbLY) };
		return vec;
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbRX),0.0f,static_cast<float>(m_padState[padNum].ThumbRY) };
		return vec;
	}
	return Vec3();
}

Vec3 Input::GetStickUnitVector(int input, int padNum) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbLX),0.0f,static_cast<float>(m_padState[padNum].ThumbLY) };
		return vec.GetNormalized();
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbRX),0.0f,static_cast<float>(m_padState[padNum].ThumbRY) };
		return vec.GetNormalized();
	}
	return Vec3();
}

float Input::GetStickVectorLength(int input, int padNum) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbLX),0.0f,static_cast<float>(m_padState[padNum].ThumbLY) };
		return vec.Length();
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState[padNum].ThumbRX),0.0f,static_cast<float>(m_padState[padNum].ThumbRY) };
		return vec.Length();
	}
	return 0.0f;
}

float Input::GetStickThumbX(int input, int padNum) const
{
	if (input == INPUT_LEFT_STICK) {
		return static_cast<float>(m_padState[padNum].ThumbLX);
	}
	if (input == INPUT_RIGHT_STICK) {
		return static_cast<float>(m_padState[padNum].ThumbRX);
	}
	return 0.0f;
}

float Input::GetStickThumbY(int input, int padNum) const
{
	if (input == INPUT_LEFT_STICK) {
		return static_cast<float>(m_padState[padNum].ThumbLY);
	}
	if (input == INPUT_RIGHT_STICK) {
		return static_cast<float>(m_padState[padNum].ThumbRY);
	}
	return 0.0f;
}

int Input::GetPadNum()
{
	return _padNum;
}

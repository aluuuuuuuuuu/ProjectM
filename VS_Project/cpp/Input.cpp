#include "Input.h"

void Input::Update()
{
	// 以前のステートを保存
	m_lastPadState = m_padState;

	// 現在のステートを取得
	GetJoypadXInputState(DX_INPUT_PAD1, &m_padState);
}

// 押した瞬間
bool Input::IsTrigger(int input) const
{
	if (input == INPUT_A) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_A] && m_padState.Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_B] && m_padState.Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_X] && m_padState.Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_Y] && m_padState.Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_UP] && m_padState.Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_DOWN] && m_padState.Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_LEFT] && m_padState.Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && m_padState.Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_START] && m_padState.Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_BACK] && m_padState.Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_THUMB] && m_padState.Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_THUMB] && m_padState.Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && m_padState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (!m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && m_padState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState.LeftTrigger <= 0 && m_padState.LeftTrigger >= 1);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState.RightTrigger <= 0 && m_padState.RightTrigger >= 1);
	}

	return false;
}

// 押している間
bool Input::IsHold(int input) const
{
	if (input == INPUT_A) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_A] && m_padState.Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_B] && m_padState.Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_X] && m_padState.Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_Y] && m_padState.Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_UP] && m_padState.Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_DOWN] && m_padState.Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_LEFT] && m_padState.Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && m_padState.Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_START] && m_padState.Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_BACK] && m_padState.Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_THUMB] && m_padState.Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_THUMB] && m_padState.Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && m_padState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && m_padState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState.LeftTrigger >= 1 && m_padState.LeftTrigger >= 1);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState.RightTrigger >= 1 && m_padState.RightTrigger >= 1);
	}
	return false;
}

// 離した瞬間
bool Input::IsRelease(int input) const
{
	if (input == INPUT_A) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_A] && !m_padState.Buttons[XINPUT_BUTTON_A]);
	}
	if (input == INPUT_B) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_B] && !m_padState.Buttons[XINPUT_BUTTON_B]);
	}
	if (input == INPUT_X) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_X] && !m_padState.Buttons[XINPUT_BUTTON_X]);
	}
	if (input == INPUT_Y) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_Y] && !m_padState.Buttons[XINPUT_BUTTON_Y]);
	}
	if (input == INPUT_UP) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_UP] && !m_padState.Buttons[XINPUT_BUTTON_DPAD_UP]);
	}
	if (input == INPUT_DOWN) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !m_padState.Buttons[XINPUT_BUTTON_DPAD_DOWN]);
	}
	if (input == INPUT_LEFT) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_LEFT] && !m_padState.Buttons[XINPUT_BUTTON_DPAD_LEFT]);
	}
	if (input == INPUT_RIGHT) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && !m_padState.Buttons[XINPUT_BUTTON_DPAD_RIGHT]);
	}
	if (input == INPUT_START) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_START] && !m_padState.Buttons[XINPUT_BUTTON_START]);
	}
	if (input == INPUT_BACK) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_BACK] && !m_padState.Buttons[XINPUT_BUTTON_BACK]);
	}
	if (input == INPUT_LEFT_PUSH) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_THUMB] && !m_padState.Buttons[XINPUT_BUTTON_LEFT_THUMB]);
	}
	if (input == INPUT_RIGHT_PUSH) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_THUMB] && !m_padState.Buttons[XINPUT_BUTTON_RIGHT_THUMB]);
	}
	if (input == INPUT_LEFT_SHOULDER) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] && !m_padState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]);
	}
	if (input == INPUT_RIGHT_SHOULDER) {
		return (m_lastPadState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !m_padState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]);
	}
	if (input == INPUT_LEFT_TRIGGER) {
		return (m_lastPadState.LeftTrigger >= 1 && m_padState.LeftTrigger <= 0);
	}
	if (input == INPUT_RIGHT_TRIGGER) {
		return (m_lastPadState.RightTrigger >= 1 && m_padState.RightTrigger <= 0);
	}
	return false;
}

Vec3 Input::GetStickVector(int input) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbLX),0.0f,static_cast<float>(m_padState.ThumbLY) };
		return vec;
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbRX),0.0f,static_cast<float>(m_padState.ThumbRY) };
		return vec;
	}
	return Vec3();
}

Vec3 Input::GetStickUnitVector(int input) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbLX),0.0f,static_cast<float>(m_padState.ThumbLY) };
		return vec.GetNormalized();
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbRX),0.0f,static_cast<float>(m_padState.ThumbRY) };
		return vec.GetNormalized();
	}
	return Vec3();
}

float Input::GetStickVectorLength(int input) const
{
	if (input == INPUT_LEFT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbLX),0.0f,static_cast<float>(m_padState.ThumbLY) };
		return vec.Length();
	}
	if (input == INPUT_RIGHT_STICK) {
		Vec3 vec = { static_cast<float>(m_padState.ThumbRX),0.0f,static_cast<float>(m_padState.ThumbRY) };
		return vec.Length();
	}
	return 0.0f;
}

float Input::GetStickThumbX(int input) const
{
	if (input == INPUT_LEFT_STICK) {
		return static_cast<float>(m_padState.ThumbLX);
	}
	if (input == INPUT_RIGHT_STICK) {
		return static_cast<float>(m_padState.ThumbRX);
	}
	return 0.0f;
}

float Input::GetStickThumbY(int input) const
{
	if (input == INPUT_LEFT_STICK) {
		return static_cast<float>(m_padState.ThumbLY);
	}
	if (input == INPUT_RIGHT_STICK) {
		return static_cast<float>(m_padState.ThumbRY);
	}
	return 0.0f;
}

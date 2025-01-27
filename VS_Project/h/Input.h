#pragma once
#include <array>
#include "DxLib.h"
#include "Singleton.h"
#include "Vec3.h"

// �e�p�b�h
#define INPUT_PAD_1 0
#define INPUT_PAD_2 1
#define INPUT_PAD_3 2
#define INPUT_PAD_4 3

// �e�{�^���̒萔
#define INPUT_A 0
#define INPUT_B 1
#define INPUT_X 2
#define INPUT_Y 3
#define INPUT_UP 4
#define INPUT_DOWN 5
#define INPUT_LEFT 6
#define INPUT_RIGHT 7
#define INPUT_START 8
#define INPUT_BACK 9
#define INPUT_LEFT_PUSH 10
#define INPUT_RIGHT_PUSH 11
#define INPUT_LEFT_SHOULDER 12
#define INPUT_RIGHT_SHOULDER 13
#define INPUT_LEFT_TRIGGER 14
#define INPUT_RIGHT_TRIGGER 15
#define INPUT_LEFT_STICK 16
#define INPUT_RIGHT_STICK 17

// DX���C�u�����Œ񋟂����\���̂̒��g
// struct XINPUT_STATE
// {
// 	 unsigned char	Buttons[16];	// �{�^���P�U��( �Y���ɂ� XINPUT_BUTTON_DPAD_UP �����g�p����A
// 	 			0:������Ă��Ȃ�  1:������Ă��� )
// 	 unsigned char	LeftTrigger;	// ���g���K�[( 0�`255 )
//	 unsigned char	RightTrigger;	// �E�g���K�[( 0�`255 )
//	 short		ThumbLX;	// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
//	 short		ThumbLY;	// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
//	 short		ThumbRX;	// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
//	 short		ThumbRY;	// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
// };

// �C���v�b�g����񋟂���V���O���g���N���X
class Input : public Singleton<Input>
{
	friend class Singleton<Input>;

public:
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �������u�Ԃ��Ƃ�
	/// </summary>
	/// <param name="input">�{�^��</param>
	/// <param name="padNum">�p�b�h�i���o�[</param>
	/// <returns>�������u��true</returns>
	bool IsTrigger(int input, int padNum) const;
	

	/// <summary>
	/// �����Ă���Ԃ��Ƃ�
	/// </summary>
	/// <param name="input">�{�^��</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>���������Ă����true</returns>
	bool IsHold(int input, int padNum) const;

	/// <summary>
	/// �������u�Ԃ��Ƃ�
	/// </summary>
	/// <param name="input">�{�^��</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�������u��true</returns>
	bool IsRelease(int input, int padNum) const;

	/// <summary>
	/// �����ꂩ�̃{�^����������Ă��邩�ǂ����Ԃ�
	/// </summary>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>������������Ă��邩�ǂ���</returns>
	bool AnyPressButton(int padNum) const;

	/// <summary>
	/// �X�e�B�b�N���͂̃x�N�g����Ԃ�
	/// </summary>
	/// <param name="input">�X�e�B�b�N</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�X�e�B�b�N���X���Ă�������̃x�N�g��</returns>
	Vec3 GetStickVector(int input, int padNum) const;

	/// <summary>
	/// �X�e�B�b�N���͂̒P�ʃx�N�g����Ԃ�
	/// </summary>
	/// <param name="input">�X�e�B�b�N</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�X�e�B�b�N���X���Ă�������̒P�ʃx�N�g��</returns>
	Vec3 GetStickUnitVector(int input, int padNum) const;

	/// <summary>
	/// �X�e�B�b�N�̌X�����Ԃ�
	/// </summary>
	/// <param name="input">�X�e�B�b�N</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�X�e�B�b�N���͂̃x�N�g���̒���</returns>
	float GetStickVectorLength(int input, int padNum) const;

	/// <summary>
	/// �X�e�B�b�N���X����X�l��Ԃ�
	/// </summary>
	/// <param name="input">�X�e�B�b�N</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�X�e�B�b�N���X���Ă�x�N�g����X�̒l</returns>
	float GetStickThumbX(int input, int padNum) const;

	/// <summary>
	/// �X�e�B�b�N���X����Y�l��Ԃ�
	/// </summary>
	/// <param name="input">�X�e�B�b�N</param>
	/// <param name="padNum">�p�b�h�i���o�[<</param>
	/// <returns>�X�e�B�b�N���X���Ă�x�N�g����Y�̒l</returns>
	float GetStickThumbY(int input, int padNum) const;

	/// <summary>
	/// �ڑ�����Ă���R���g���[���[�̐����擾����
	/// </summary>
	/// <returns>�R���g���[���[�̐�</returns>
	int GetPadNum();

private:
	// ���t���[���̃C���v�b�g�X�e�[�g
	XINPUT_STATE _padState[4] = {};

	// �O�t���[���̃C���v�b�g�X�e�[�g
	XINPUT_STATE _lastPadState[4] = {};

	// �v���C�x�[�g�R���X�g���N�^
	Input() {};

	// �ڑ�����Ă���R���g���[���[�̐�
	int _padNum = 0;
};


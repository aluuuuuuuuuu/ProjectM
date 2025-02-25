#pragma once
#include "Vec2.h"

constexpr int SOLO_MODE = 0;
constexpr int MULTI_MODE = 1;
constexpr int TUTORIAL_MODE = 2;
constexpr int OPTION_MODE = 3;

class SelectModeUi
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SelectModeUi();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SelectModeUi();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:

	// �I�����Ă��鍀�ڂ̔ԍ�
	int _selectButtonNum;

	// �����̉~�̃n���h��
	int _circleHandle;

	// �����̉~�̍��W
	Vec2 _circlePos;

	double _circleAngle;

	// �e�{�^���n���h��
	int _buttonHandle[3];

	// �{�^���̍��W
	Vec2 _buttonPos[3];

	// �{�^���̊g�嗦
	double _buttonScale[3];

	// ���̃��b�Z�[�W�n���h��
	int _messageHandle[3];

};


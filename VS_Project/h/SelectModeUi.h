#pragma once
#include "Vec2.h"

constexpr int SOLO_MODE = 0;
constexpr int MULTI_MODE = 1;
constexpr int TUTORIAL_MODE = 2;
constexpr int OPTION_MODE = 3;

constexpr float SOLO_ANGLE = 315.0f;
constexpr float MULTI_ANGLE = 45.0f;
constexpr float TUTORIAL_ANGLE = 225.0f;
constexpr float OPTION_ANGLE = 135.0f;

constexpr int PLAYER_NUM_1 = 0;
constexpr int PLAYER_NUM_2 = 1;
constexpr int PLAYER_NUM_3 = 2;
constexpr int PLAYER_NUM_4 = 3;

constexpr int MARGIN_X = 90;
constexpr int MARGIN_Y = 90;

class SelectModeUi
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="selectMode">true:�Z���N�g���[�h</param>
	SelectModeUi(bool selectMode);

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

	/// <summary>
	/// �I�����Ă���{�^�����擾����
	/// </summary>
	/// <returns>�I�����Ă���{�^��</returns>
	int GetSelect() const;
private:

	// �t���[���J�E���^
	int _frame;

	// �I�����Ă��鍀�ڂ̔ԍ�
	int _selectButtonNum;

	// �����̉~�̃n���h��
	int _circleHandle[4];

	// �����̃��S�n���h��
	int _circleLogoHandle;

	// �����̖��
	int _centerArrowHandle[4];

	// �I�����Ă�������ɔ����]����\������摜�n���h��
	int _marginHandle[4];

	// �����̉~�̍��W
	Vec2 _circlePos;

	// �~�̊g�嗦
	double _circleScale;

	// �~�̊p�x
	double _circleAngle;

	// �e�{�^���n���h��
	int _buttonHandle[4];

	// �t���[���n���h��
	int _frameHandle[4];

	// �{�^���̍��W
	Vec2 _buttonPos[4];

	// �I�����Ă���{�^����ڗ�������摜�n���h��	
	int _highlightHandle[4];

	// ���̃��b�Z�[�W�n���h��
	int _messageHandle[4];

	// �I����؂�ւ���frag
	bool _changeFrag;

	// �O�t���[���őI�����Ă����{�^��
	int _oldSelectButtonNum;

	// �I�񂾍��ڂɂ���đS�̂̉摜�̈ʒu����点��
	Vec2 _marginPos;

	bool _input;

	// ���̈ړ��x�N�g��
	Vec2 _arrowVec;

	// �~�̊g�嗦
	float _scale = 0.0f;
};


#pragma once
#include "Vec2.h"

class SceneTitle;
class AnyPushButton
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�^�C�g���V�[���̎Q��</param>
	AnyPushButton(SceneTitle& scene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~AnyPushButton();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;
private:	

	// ���͉摜�̃n���h��
	int _textHandle;

	// �\���ʒu
	Vec2 _dispPos;

	// �t���[���J�E���g
	int _frame;
};


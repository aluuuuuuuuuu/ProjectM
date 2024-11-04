#pragma once
#include "Singleton.h"

class SoundManager:
	public Singleton<SoundManager>
{
public:

	/// <summary>
	/// ��������
	/// </summary>
	void Init();

	/// <summary>
	/// �I�[�v�j���O�̃e�[�}���Đ��J�n����
	/// </summary>
	void StartOp();

	/// <summary>
	/// �I�[�v�j���O�̃e�[�}���Đ���~����
	/// </summary>
	void StopOp();

	/// <summary>
	/// �^�C�g����ʂŃ{�^�����������Ƃ��̉���炷
	/// </summary>
	void RingStartSE();

private:

	// �I�[�v�j���O�̃e�[�}
	int _opBGM;

	// �^�C�g����ʂŃ{�^�����������Ƃ��̉�
	int _startSE;

};


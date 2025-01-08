#pragma once
#include "Singleton.h"

#define VOLUME_MIN 85
#define VOLUME_MIDDLE 170
#define VOLUME_MAX 255
#define VOLUME_ZERO 0

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

	/// <summary>
	/// BGM�̉��ʂ�ݒ肷��
	/// </summary>
	/// <param name="volume">���ʒ萔</param>
	void SetVolumeBGM(int volume);

	/// <summary>
	/// SE�̉��ʂ�ݒ肷��
	/// </summary>
	/// <param name="volume">���ʒ萔</param>
	void SetVolumeSE(int volume);

	/// <summary>
	/// BGM�̉��ʂ�Ԃ�
	/// </summary>
	/// <returns>BGM�̉���</returns>
	int GetVolumeBGM();

	/// <summary>
	/// SE�̉��ʂ�Ԃ�
	/// </summary>
	/// <returns>SE�̉���</returns>
	int GetVolumeSE();

private:

	// �I�[�v�j���O�̃e�[�}
	int _opBGM = 0;

	// �^�C�g����ʂŃ{�^�����������Ƃ��̉�
	int _startSE = 0;

	// BGM����
	int _volumeBGM = VOLUME_MIDDLE;
	
	// SE����
	int _volumeSE = VOLUME_MIDDLE;
};


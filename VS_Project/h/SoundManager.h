#pragma once
#include "Singleton.h"
#include <map>

constexpr int  VOLUME_MIN = 85;
constexpr int  VOLUME_MIDDLE = 170;
constexpr int  VOLUME_MAX = 255;
constexpr int  VOLUME_ZERO = 0;

constexpr int BGM_OPENING = 0;
constexpr int BGM_BATTLE = 1;
constexpr int BGM_THEME = 2;

constexpr int SE_NUM_SELECT = 0;
constexpr int SE_TITLE_START = 1;
constexpr int SE_CHARA_SELECT = 2;
constexpr int SE_CHARA_CANCEL = 3;
constexpr int SE_GAME_START = 4;
constexpr int SE_RESULT = 5;
constexpr int SE_SHOUT = 6;
constexpr int SE_BEEP = 7;
constexpr int SE_OPEN_MENU = 8;
constexpr int SE_CLOSE_MENU = 9;
constexpr int SE_BULLET_SELECT = 10;
constexpr int SE_SHOT_NORMAL_BULET = 11;
constexpr int SE_SHOT_GRAPPLE_BULET = 12;
constexpr int SE_SHOT_BOMB_BULET = 13;
constexpr int SE_EXPLOSION = 14;
constexpr int SE_DESTRUCTION = 15;
constexpr int SE_GRAPPLE = 16;
constexpr int SE_KO = 17;



class SoundManager:
	public Singleton<SoundManager>
{
public:

	/// <summary>
	/// ��������
	/// </summary>
	void Init();

	/// <summary>
	/// BGM���X�^�[�g������
	/// </summary>
	/// <param name="bgm">bgm�萔��</param>
	void StartBGM(int bgm);

	/// <summary>
	/// BGM���X�g�b�v������
	/// </summary>
	/// <param name="bgm">bgm�萔��</param>
	void StopBGM(int bgm);

	/// <summary>
	/// SE��炷
	/// </summary>
	/// <param name="se">se�萔��</param>
	void RingSE(int se);

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

	// BGM����
	int _volumeBGM = VOLUME_MIDDLE;
	
	// SE����
	int _volumeSE = VOLUME_MIDDLE;

	// BGM�}�b�v
	std::map<int, int> _bgmMap;

	// SE�}�b�v
	std::map<int, int> _seMap;
};


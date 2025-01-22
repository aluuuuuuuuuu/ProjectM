#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	// âπÇÃÉçÅ[Éh

	// BGM
	{
		_bgmMap[BGM_OPENING] = LoadSoundMem("data/BGM/Title_BGM.mp3");
		_bgmMap[BGM_BATTLE] = LoadSoundMem("data/BGM/intrusion_loop.ogg");
	}

	//SE
	{
		_seMap[SE_NUM_SELECT] = LoadSoundMem("data/SE/SelectSound.mp3");
		_seMap[SE_TITLE_START] = LoadSoundMem("data/SE/StartSound.mp3");
		_seMap[SE_CHARA_SELECT] = LoadSoundMem("data/SE/CharactorSelectSound.mp3");
		_seMap[SE_CHARA_CANCEL] = LoadSoundMem("data/SE/CancelSound.mp3");
		_seMap[SE_GAME_START] = LoadSoundMem("data/SE/GameStartSound.mp3");
		_seMap[SE_RESULT] = LoadSoundMem("data/SE/Result_Victory.mp3");
		_seMap[SE_SHOUT] = LoadSoundMem("data/SE/TitleShout.mp3");
	}

	// âπó ÇÃê›íË
	// BGM
	for (auto& [key, value] : _bgmMap) {
		ChangeVolumeSoundMem(VOLUME_MIDDLE, value);
	}
	// SE
	for (auto& [key, value] : _seMap) {
		ChangeVolumeSoundMem(VOLUME_MIDDLE, value);
	}
}

void SoundManager::StartBGM(int bgm)
{
	if (CheckSoundMem(_bgmMap[bgm]) == 0) {
		PlaySoundMem(_bgmMap[bgm], DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM(int bgm)
{
	StopSoundMem(_bgmMap[bgm]);
}

void SoundManager::RingSE(int se)
{
	PlaySoundMem(_seMap[se],DX_PLAYTYPE_BACK);
}

void SoundManager::SetVolumeBGM(int volume)
{
	// âπó ÇïœçXÇ∑ÇÈ
	for (auto& [key, value] : _bgmMap) {
		ChangeVolumeSoundMem(volume, value);
	}

	// âπó Çï€ë∂Ç∑ÇÈ
	_volumeBGM = volume;
}

void SoundManager::SetVolumeSE(int volume)
{
	for (auto& [key, value] : _seMap) {
		ChangeVolumeSoundMem(volume, value);
	}

	// âπó Çï€ë∂Ç∑ÇÈ
	_volumeSE = volume;
}

int SoundManager::GetVolumeBGM()
{
	return _volumeBGM;
}

int SoundManager::GetVolumeSE()
{
	return _volumeSE;
}

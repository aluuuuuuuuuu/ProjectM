#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	// âπÇÃÉçÅ[Éh
	_opBGM = LoadSoundMem("data/BGM/Title_BGM.mp3");
	_startSE = LoadSoundMem("data/SE/StartSound.mp3");

	// âπó ÇÃê›íË
	ChangeVolumeSoundMem(VOLUME_MIDDLE, _opBGM);
	ChangeVolumeSoundMem(VOLUME_MIDDLE, _startSE);

}

void SoundManager::StartOp()
{
	if (CheckSoundMem(_opBGM) == 0) {
		PlaySoundMem(_opBGM, DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopOp()
{

	StopSoundMem(_opBGM);
}

void SoundManager::RingStartSE()
{
	PlaySoundMem(_startSE, DX_PLAYTYPE_BACK);
}

void SoundManager::SetVolumeBGM(int volume)
{
	ChangeVolumeSoundMem(volume, _opBGM);
	_volumeBGM = volume;
}

void SoundManager::SetVolumeSE(int volume)
{
	ChangeVolumeSoundMem(volume, _startSE);
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

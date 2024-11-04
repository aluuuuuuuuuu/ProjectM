#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	_opBGM = LoadSoundMem("data/BGM/Title_BGM.mp3");
	_startSE = LoadSoundMem("data/SE/StartSound.mp3");
}

void SoundManager::StartOp()
{
	PlaySoundMem(_opBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopOp()
{

	StopSoundMem(_opBGM);
}

void SoundManager::RingStartSE()
{
	PlaySoundMem(_startSE, DX_PLAYTYPE_BACK);
}

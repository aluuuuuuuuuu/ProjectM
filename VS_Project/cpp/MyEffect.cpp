#include "MyEffect.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"

MyEffect::MyEffect(int effect,Vec3 pos)
{
	_playHandle = PlayEffekseer3DEffect(EffectManager::GetInstance().GetEffectHandle(effect));
}

MyEffect::~MyEffect()
{
}

void MyEffect::Update(Vec3 pos)
{
	// �G�t�F�N�g�̈ړ�
	SetPosPlayingEffekseer3DEffect(_playHandle, pos.x, pos.y, pos.z);
}

void MyEffect::Draw() const
{
}

void MyEffect::StopEffect()
{
	StopEffekseer3DEffect(_playHandle);
}

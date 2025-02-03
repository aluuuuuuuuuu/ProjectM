#include "EffectManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"

void EffectManager::Init()
{
	// Effekseer������������
	Effekseer_Init(8000);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	for (int i = 0; i < MAX_EFFECT_NUM; i++) {
		_effectMap[i] = -1;
	}
}

void EffectManager::Draw() const
{
	// ���ӂ��������̍X�V
	UpdateEffekseer3D();

	// �J�����̓���
	Effekseer_Sync3DSetting();

	// �G�t�F�N�g�̕`��
	DrawEffekseer3D();
}

void EffectManager::Terminate()
{
	// Effekseer���I������B
	Effkseer_End();
}

int& EffectManager::GetEffectHandle(int effect)
{
	// �G�t�F�N�g�������[�h�ł���΃��[�h����
	if (_effectMap[effect] == -1) {
		 LoadEffect(effect);
	}
	
	// �n���h���̎Q�Ƃ�Ԃ�
	return _effectMap[effect];
}

void EffectManager::DeleteEffect()
{
	for (auto& [key, value] : _effectMap) {
		DeleteEffekseerEffect(value);
	}
}

void EffectManager::LoadEffect(int effect)
{
	// �����̃G�t�F�N�g�����[�h����
	switch (effect)
	{
	case NORMAL_BULLET_EFFECT:
		_effectMap[effect] =  LoadEffekseerEffect("data/effect/NormalBullet.efk",2.0f);
		break;
	case BOMB_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/BombBullet.efk", 5.0f);
		break;
	case GRAPPLE_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/GrappleBullet.efk", 5.0f);
		break;
	case BLOCK_DESTROY_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effects/test.efk", 5.0f);
		break;
	case JUMP_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/test.efk", 5.0f);
		break;
	case WIN_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/Winner.efk", 1.5f);
		break;
	case SHOT_DOWN_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/gekitui.efk", 10.0f);
		break;
	default:
		break;
	}
}

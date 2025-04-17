#include "EffectManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"

void EffectManager::Init()
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/EffectManager.csv");

	// Effekseer������������
	Effekseer_Init(GetConstantInt("MAX_PARTICLE"));

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
		_effectMap[effect] = LoadEffekseerEffect("data/effect/NormalBullet.efk", GetConstantFloat("NORMAL_BULLET_SIZE"));
		break;
	case BOMB_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/BombBullet.efk", GetConstantFloat("BOMB_BULLET_SIZE"));
		break;
	case GRAPPLE_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/GrappleBullet2.efk", GetConstantFloat("GRAPPLE_BULLET_SIZE"));
		break;
	case BLOCK_DESTROY_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effects/test.efk", GetConstantFloat("BLOCK_DESTROY_SIZE"));
		break;
	case JUMP_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/test.efk", GetConstantFloat("JUMP_SIZE"));
		break;
	case WIN_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/Winner.efk", GetConstantFloat("WIN_SIZE"));
		break;
	case SHOT_DOWN_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/gekitui.efk", GetConstantFloat("SHOT_DOWN_SIZE"));
		break;
	case SPEED_UP_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/SpeedUp.efk", GetConstantFloat("SPEED_UP_SIZE"));
		break;
	default:
		break;
	}
}

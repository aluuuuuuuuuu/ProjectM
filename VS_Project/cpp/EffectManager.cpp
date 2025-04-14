#include "EffectManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"

void EffectManager::Init()
{
	// Effekseerを初期化する
	Effekseer_Init(8000);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	for (int i = 0; i < MAX_EFFECT_NUM; i++) {
		_effectMap[i] = -1;
	}
}

void EffectManager::Draw() const
{
	// えふぇくしあの更新
	UpdateEffekseer3D();

	// カメラの同期
	Effekseer_Sync3DSetting();

	// エフェクトの描画
	DrawEffekseer3D();
}

void EffectManager::Terminate()
{
	// Effekseerを終了する。
	Effkseer_End();
}

int& EffectManager::GetEffectHandle(int effect)
{
	// エフェクトが未ロードであればロードする
	if (_effectMap[effect] == -1) {
		 LoadEffect(effect);
	}
	
	// ハンドルの参照を返す
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
	// 引数のエフェクトをロードする
	switch (effect)
	{
	case NORMAL_BULLET_EFFECT:
		_effectMap[effect] =  LoadEffekseerEffect("data/effect/NormalBullet.efk",2.0f);
		break;
	case BOMB_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/BombBullet.efk", 5.0f);
		break;
	case GRAPPLE_BULLET_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/GrappleBullet2.efk", 5.0f);
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
	case SPEED_UP_EFFECT:
		_effectMap[effect] = LoadEffekseerEffect("data/effect/SpeedUp.efk", 10.0f);
	default:
		break;
	}
}

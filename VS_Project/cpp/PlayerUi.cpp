#include "PlayerUi.h"
#include "DxLib.h"
#include "PlayerManager.h"


PlayerUi::PlayerUi(int playerNum)
{
	// 画像のロード
	_normalBulletHandle = LoadGraph("data/image/Icon_Bullet.png");
	_bombBulletHandle = LoadGraph("data/image/Icon_Bomb.png");
	_grappleBulletHandle = LoadGraph("data/image/Icon_Anchor.png");
	_reticleHandle = LoadGraph("data/image/circle.png");
	_frameHandle = LoadGraph("data/image/IconFlame.png");

	// プレイヤーの総数で座標や拡大率を変更する
	switch (playerNum)
	{
	case PLAYER_ONE:
		_drawMargin.x = 520;
		_drawMargin.y = 405;
		_margin = 150;
		_exRate = 0.2;
		break;
	case PLAYER_TWO:
		_drawMargin.x = 80;
		_drawMargin.y = 405;
		_margin = 150;
		_exRate = 0.2;
		break;
	case PLAYER_THREE:
	case PLAYER_FORE:
		_drawMargin.x = 80;
		_drawMargin.y = 202;
		_margin = 150;
		_exRate = 0.2;
		break;
	default:
		_exRate = 0.2;
		_margin = 150;
		break;
	}
}

PlayerUi::~PlayerUi()
{
	DeleteGraph(_normalBulletHandle);
	DeleteGraph(_bombBulletHandle);
	DeleteGraph(_grappleBulletHandle);
	DeleteGraph(_reticleHandle);
	DeleteGraph(_frameHandle);
}

void PlayerUi::Update()
{
	_framePos = Vec2{};
}

void PlayerUi::Draw(Vec2 center, BulletData data) const
{
	// アイコンの描画
	DrawRotaGraph(center.intX() + _drawMargin.intX(), center.intY() + _drawMargin.intY(), _exRate, 0.0, _normalBulletHandle, true);
	DrawRotaGraph(center.intX() + _drawMargin.intX() + _margin, center.intY() + _drawMargin.intY(), _exRate, 0.0, _grappleBulletHandle, true);
	DrawRotaGraph(center.intX() + _drawMargin.intX() + _margin * 2, center.intY() + _drawMargin.intY(), _exRate, 0.0, _bombBulletHandle, true);

	// アイコンフレームの描画
	switch (data._selectBullet)
	{
	case NORMAL_BULLET:
		DrawRotaGraph(center.intX() + _drawMargin.intX(), center.intY() + _drawMargin.intY(), _exRate, 0.0, _frameHandle, true);
		break;
	case GRAPPLER_BULLET:
		DrawRotaGraph(center.intX() + _drawMargin.intX() + _margin, center.intY() + _drawMargin.intY(), _exRate, 0.0, _frameHandle, true);
		break;
	case BOMB_BULLET:
		DrawRotaGraph(center.intX() + _drawMargin.intX() + _margin * 2, center.intY() + _drawMargin.intY(), _exRate, 0.0, _frameHandle, true);
		break;
	default:
		break;
	}

	// クールタイムを四角形で描画
	int margin = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	if (data._bullletCoolTime[NORMAL_BULLET] != 0) {

		margin = 100 /  (30 / data._bullletCoolTime[NORMAL_BULLET]);
		DrawBox(center.intX() - 50 + _drawMargin.intX(), center.intY() + 50 + _drawMargin.intY() - margin, center.intX() + 50 + _drawMargin.intX(), center.intY() + 50 + _drawMargin.intY(), 0x16fff9, true);
	}

	if (data._bullletCoolTime[GRAPPLER_BULLET] != 0) {
		margin = 100 / (300 / data._bullletCoolTime[GRAPPLER_BULLET]);
		DrawBox(center.intX() - 50 + _drawMargin.intX() + _margin, center.intY() + 50 + _drawMargin.intY() - margin, center.intX() + 50 + _drawMargin.intX() + _margin, center.intY() + 50 + _drawMargin.intY(), 0x16fff9, true);
	}

	if (data._bullletCoolTime[BOMB_BULLET] != 0) {
		margin = 100 / (120 / data._bullletCoolTime[BOMB_BULLET]);
		DrawBox(center.intX() - 50 + _drawMargin.intX() + _margin * 2, center.intY() + 50 + _drawMargin.intY() - margin, center.intX() + 50 + _drawMargin.intX() + _margin * 2, center.intY() + 50 + _drawMargin.intY(), 0x16fff9, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	//レティクルの描画
	DrawRotaGraph(center.intX(), center.intY(), 1.0, 0.0, _reticleHandle, true);
}
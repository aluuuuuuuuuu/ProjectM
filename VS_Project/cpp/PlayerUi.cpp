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
		_drawMargin.x = 270;
		_drawMargin.y = 405;
		_margin = 150;
		_exRate = 0.2;
		break;
	case PLAYER_THREE:
	case PLAYER_FORE:
		_drawMargin.x = 270;
		_drawMargin.y = 202;
		_margin = 150;
		_exRate = 0.2;
		break;
	default:
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
	DrawRotaGraph(center.x + _drawMargin.x, center.y + _drawMargin.y, _exRate, 0.0, _normalBulletHandle, true);
	DrawRotaGraph(center.x + _drawMargin.x + _margin, center.y + _drawMargin.y, _exRate, 0.0, _grappleBulletHandle, true);
	DrawRotaGraph(center.x + _drawMargin.x + _margin * 2, center.y + _drawMargin.y, _exRate, 0.0, _bombBulletHandle, true);

	// アイコンフレームの描画
	switch (data._selectBullet)
	{
	case NORMAL_BULLET:
		DrawRotaGraph(center.x + _drawMargin.x, center.y + _drawMargin.y, _exRate, 0.0, _frameHandle, true);
		break;
	case GRAPPLER_BULLET:
		DrawRotaGraph(center.x + _drawMargin.x + _margin, center.y + _drawMargin.y, _exRate, 0.0, _frameHandle, true);
		break;
	case BOMB_BULLET:
		DrawRotaGraph(center.x + _drawMargin.x + _margin * 2, center.y + _drawMargin.y, _exRate, 0.0, _frameHandle, true);
		break;
	default:
		break;
	}


	//レティクルの描画
	DrawRotaGraph(center.intX(), center.intY(), 1.0, 0.0, _reticleHandle, true);
}
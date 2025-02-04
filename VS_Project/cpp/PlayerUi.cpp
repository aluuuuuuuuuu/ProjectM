#include "PlayerUi.h"
#include "DxLib.h"
#include "PlayerManager.h"
#include <cmath>


PlayerUi::PlayerUi(int playerNum):
	_frame(0.0f)
{
	// �摜�̃��[�h
	_normalBulletHandle = LoadGraph("data/image/Icon_Bullet.png");
	_bombBulletHandle = LoadGraph("data/image/Icon_Bomb.png");
	_grappleBulletHandle = LoadGraph("data/image/Icon_Anchor.png");
	_reticleHandle = LoadGraph("data/image/circle.png");
	_frameHandle = LoadGraph("data/image/IconFlame.png");

	// �v���C���[�̑����ō��W��g�嗦��ύX����
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
	_frame += 0.1f;	// ���Ԍo��
	_exRate = 0.2 +  0.04 * sin(_frame); // y���W�i�U��50�̃T�C���g�j
}

void PlayerUi::Draw(Vec2 center, BulletData data) const
{

	// �\�����W
	int x, y;

	x = center.intX() + _drawMargin.intX();
	y = center.intY() + _drawMargin.intY();

	// �A�C�R���̕`��
	DrawRotaGraph(x, y, 0.2f, 0.0, _normalBulletHandle, true);
	DrawRotaGraph(x + _margin, y, 0.2f, 0.0, _grappleBulletHandle, true);
	DrawRotaGraph(x + _margin * 2, y, 0.2f, 0.0, _bombBulletHandle, true);

	// �A�C�R���t���[���̕`��
	switch (data._selectBullet)
	{
	case NORMAL_BULLET:
		DrawRotaGraph(x, y, _exRate, 0.0, _frameHandle, true);
		break;
	case GRAPPLER_BULLET:
		DrawRotaGraph(x + _margin, y, _exRate, 0.0, _frameHandle, true);
		break;
	case BOMB_BULLET:
		DrawRotaGraph(x + _margin * 2, y, _exRate, 0.0, _frameHandle, true);
		break;
	default:
		break;
	}

	// �N�[���^�C�����l�p�`�ŕ`��
	double margin = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	if (data._bullletCoolTime[NORMAL_BULLET] != 0) {
		auto rate = static_cast<float>(data._bullletCoolTime[NORMAL_BULLET] / 30.0f);
		margin = 100 * rate ;
		DrawBox(x - 50, y + 50 - static_cast<int>(margin), x + 50, y + 50, 0xd30707, true);
	}

	if (data._bullletCoolTime[GRAPPLER_BULLET] != 0) {
		auto rate = static_cast<float>(data._bullletCoolTime[GRAPPLER_BULLET] / 300.0f);
		margin = 100 * rate;
		DrawBox(x - 50 + _margin, y + 50 - static_cast<int>(margin), x + 50 + _margin, y + 50, 0xd30707, true);
	}

	if (data._bullletCoolTime[BOMB_BULLET] != 0) {

		auto rate = static_cast<float>(data._bullletCoolTime[BOMB_BULLET] / 300.0f);
		margin = 100 * rate;
		DrawBox(x - 50 + _margin * 2, y + 50 - static_cast<int>(margin), x + 50 + _margin * 2, y + 50, 0xd30707, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//���e�B�N���̕`��
	DrawRotaGraph(center.intX(), center.intY(), 1.0, 0.0, _reticleHandle, true);
}
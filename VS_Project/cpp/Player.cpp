#include "Player.h"
#include "DxLib.h"
#include "Input.h"

Player::Player()
{
	// 拡大の設定
	Scale = Vec3{ 1.0f,1.0f,1.0f };

	// 座標の設定
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// カプセルの初期化
	InitCapsule(Position, 10.0f, 10);
}

Player::~Player()
{
}

void Player::Update()
{
	// とりあえず移動
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		Position.x += 1;
	}

	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		Position.x -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_DOWN)) {
		Position.z -= 1;
	}

	if (Input::getInstance().IsHold(INPUT_UP)) {
		Position.z += 1;
	}

	// とりあえず落下
	if (Input::getInstance().IsHold(INPUT_A)) {
		Position.y -= 1;
	}
	if (Input::getInstance().IsHold(INPUT_Y)) {
		Position.y += 1;
	}

	//Position.y -= 0.5f;
	

	// カプセルに座標を渡す
	Set(Position);
}

void Player::Draw() const
{

	// カプセルを描画
	DrawCapsule();
}

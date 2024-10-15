#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "StageCollisionManager.h"

Player::Player(std::shared_ptr<StageCollisionManager>& col):
	_yMoveScale(0),
	_isGround(false),
	_collManager(col)
{
	// 拡大の設定
	Scale = Vec3{ 1.0f,1.0f,1.0f };

	// 座標の設定
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// カプセルの初期化
	InitCapsule(Position, 4.0f, 10);
}

Player::~Player()
{
}

void Player::Update()
{
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// 移動ベクトルの初期化
	_moveVec = 0;

	if (_isGround) DrawString(10, 30, "OnGround", 0xffffff);

	// 座標に移動ベクトルを加算する
	Position += CreateMoveVec();

	// ジャンプと重力を足したものを座標に足す
	Position.y += CreateYMoveScale();

	// コリジョンの判定をする
	Position += _collManager->CapsuleCollision(_data);

	// カプセルに座標を渡す
	Set(Position);

	// 地上にいるか判定する
	_isGround = OnGround();

	_frontPos = Position;

}

void Player::Draw() const
{

	// カプセルを描画
	DrawCapsule();
}

void Player::SetPos(Vec3 pos)
{
	Position = pos;
	Set(pos);
}

Vec3 Player::CreateMoveVec()
{
	// 移動量を返すベクトル
	Vec3 move;

	// とりあえず移動
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		move.x += 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		move.x -= 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_DOWN)) {
		move.z -= 1.0f;
	}

	if (Input::getInstance().IsHold(INPUT_UP)) {
		move.z += 1.0f;
	}

	return move.GetNormalized();
}

float Player::CreateYMoveScale()
{
	
	// 地上にいなかったら
	// 一定の落下速度になるまで落下速度を上げる
	//if (_isGround) {

	//}
	//else {

	if (_yMoveScale > -1.5f) {
		_yMoveScale -= 0.1f;
	}
	//}

	// Aボタンでジャンプ
	if (Input::getInstance().IsHold(INPUT_A) && _isGround) {

		// ジャンプ力を与える
		_yMoveScale = 2.0f;
	}

	return _yMoveScale;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		return true;
	}

	return false;
}

#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "NormalBullet.h"
#include "BulletManager.h"
#include "BulletBase.h"
#include "PlayerManager.h"

Player::Player( std::shared_ptr<BulletManager>& bullet, PlayerManager& manager, int padNum) :
	_moveScaleY(0),
	_isGround(false),
	_bulletManager(bullet),
	_groundCount(0),
	_runFlag(false),
	_padNum(padNum),
	_manager(manager),
	_bulletNum(15)
{
	// 拡大の設定
	Scale = Vec3{ 0.12f,0.12f,0.12f };

	// モデルの初期処理
	InitModel(_manager.GetModelHandle(padNum));

	// 座標の設定
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// カプセルの初期化
	InitCapsule(Position, 3.0f, 12);

	// アニメーションの初期処理
	InitAnimation(_modelHandle, _manager.GetConstantInt("ANIM_AIMING_IDLE"), _manager.GetConstantFloat("BLEND_RATE"));

	// カメラの作成
	_pCamera = std::make_shared<PlayerCamera>(Position, _padNum);
}

Player::~Player()
{
}

void Player::Control()
{
	// 弾を発射する
	if (Input::GetInstance().IsTrigger(INPUT_RIGHT_SHOULDER, _padNum) && _bulletNum > 0) {

		// 撃つときに走っていたら歩きにする
		if (_runFlag) {
			_runFlag = false;
		}

		// 発射する座標
		Vec3 pos = { Position.x  ,Position.y + 10 ,Position.z };

		// 弾を生成
		_bulletManager->PushBullet(NORMAL_BULLET, RotateBulletVec(Position,_pCamera->Position), pos);

		_bulletNum--;
	}

	// リロード
	if (Input::GetInstance().IsTrigger(INPUT_Y, _padNum)) {
		_bulletNum = 15;
	}
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f angleY:%f", Position.x, Position.y, Position.z, Angle.y);

	// 移動ベクトルの初期化
	_moveVec = 0;

	if (_isGround) DrawString(10, 30, "OnGround", 0xffffff);

	// 移動
	Move();

	// 自身の回転値を更新する
	Rotate();
	
	// カプセルに座標を渡す
	Set(Position);
}

void Player::Update()
{
	// カプセルに座標を渡す
	Set(Position);

	// 地上にいるか判定する
	_isGround = OnGround();

	_frontPos = Position;

	// カメラの更新
	_pCamera->Update(Position);

	// アニメーションコントロール
	AnimationContorol();

	// アニメーションの更新
	if (_runFlag && _isGround) {

		// 走っているときのアニメーション速度で更新する
		UpdateAnimation(_modelHandle, _manager.GetConstantFloat("ANIM_SPEED_RUN"));
	}
	else {

		// 歩き
		UpdateAnimation(_modelHandle, _manager.GetConstantFloat("ANIM_SPEED_WALK"));
	}

	// モデルの更新
	UpdateModel(GetTransformInstance());
}

void Player::Draw() const
{

#ifdef _DEBUG
	//カプセルを描画
	DrawCapsule();
#endif // DEBUG
	DrawModel();
}

void Player::CameraSet() const
{
	SetCameraPositionAndTarget_UpVecY(_pCamera->Position.VGet(), _pCamera->GetTarget().VGet());
}

bool Player::GetGroundFlag() const
{
	return _isGround;
}

void Player::Rotate()
{
	// 歩き中はカメラと同じ方向を向く
	if (!_runFlag) {
		RotateAngleY(_pCamera->Angle.y);
	}
	// 走り中は移動方向を向く
	else {

		float targetAngle;

		// 移動する方向の角度を求める
		Vec3 targetPos = Position + _moveVec;
		float x = targetPos.x - Position.x;
		float z = targetPos.z - Position.z;
		targetAngle = atan2f(x, z);
		targetAngle = targetAngle + static_cast<float>(DX_PI);
		DX_TWO_PI;

		RotateAngleY(targetAngle);
	}
}

void Player::Move()
{

	// Xボタンでダッシュ切り替え
	if (Input::GetInstance().IsTrigger(INPUT_X, _padNum)) {
		_runFlag = !_runFlag;
	}

	// xz軸方向の移動
	CreateMoveVec();

	// Y軸方向の移動
	CreateYMoveScale();

	// 移動ベクトルをy軸回転させる
	_moveVec = RotateMoveVec(_moveVec, _pCamera->Angle.y);

	// 座標に移動ベクトルを足す
	Position += _moveVec;
}

Vec3 Player::RotateMoveVec(Vec3 vec, float angle)
{
	Vec3 ret;

	// Y軸回転行列に変換
	MATRIX rotaMtx = MGetRotY(angle);

	ret = Vec3{ vec.x * -1, vec.y, vec.z * -1 };

	// 移動ベクトルを回転値に合わせてY軸回転させる
	ret = VTransform(ret.VGet(), rotaMtx);

	return ret;
}

void Player::CreateMoveVec()
{
	// 移動量を返すベクトル
	Vec3 move;

	// スティックの入力値を移動ベクトルに代入する
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, _padNum) > 3000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, _padNum);
	}

	if (_runFlag) {
		_moveVec += move * _manager.GetConstantFloat("RUN_SPEED");
	}
	else {
		_moveVec += move * _manager.GetConstantFloat("WALK_SPEED");
	}

	DrawFormatString(30, 50, 0xffffff, "%f %f %f", _moveVec.x, _moveVec.y, _moveVec.x);
}

void Player::CreateYMoveScale()
{

	// 地上にいなかったら
	// 一定の落下速度になるまで落下速度を上げる
	if (_isGround) {
		//_moveScaleY = 0.1f;
	}
	else {

		if (_moveScaleY > -1.5f) {
			_moveScaleY -= 0.1f;
		}
	}

	// Aボタンでジャンプ
	if (Input::GetInstance().IsHold(INPUT_A, _padNum) && _isGround) {

		// ジャンプ力を与える
		_moveScaleY = 2.0f;

		// ジャンプの開始アニメーションを再生
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_JUMP_UP"), false, _manager.GetConstantFloat("BLEND_RATE"));
	}

	_moveVec.y += _moveScaleY;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		if (_groundCount == 0) {
			_groundCount++;
		}
		else {
			return true;
		}
	}
	else {
		_groundCount = 0;
	}

	return false;
}

void Player::RotateAngleY(float targetAngle)
{
	// 平行移動ベクトルが0じゃないときだけ角度を計算する
	if (_moveVec.x != 0.0f && _moveVec.z != 0.0f) {
		// 移動する方向に徐々に回転する

		// 差が移動量より小さくなったら目標の値を代入する
		if (fabsf(Angle.y - targetAngle) > _manager.GetConstantFloat("ANGLE_ROTATE_SCALE")) {
			// 増やすのと減らすのでどちらが近いか判断する
			float add = targetAngle - Angle.y;	// 足す場合の回転量
			if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// 足す場合の回転量が負の数だった場合正規化する
			float sub = static_cast<float>(DX_TWO_PI) - add;	// 引く場合の回転量

			// 回転量を比べて少ない方を選択する
			if (add < sub) {
				Angle.y += _manager.GetConstantFloat("ANGLE_ROTATE_SCALE");
			}
			else {
				Angle.y -= _manager.GetConstantFloat("ANGLE_ROTATE_SCALE");
			}

			// 増減によって範囲外になった場合の正規化
			Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
			if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
		}
		else {
			Angle.y = targetAngle;
		}
	}
}

void Player::RotateAngleToCamera()
{
	float targetAngle = _pCamera->Angle.y;

	RotateAngleY(targetAngle);
}

void Player::RotateAngleToVec()
{
	float targetAngle = Angle.y;

	RotateAngleY(targetAngle);
}

int Player::ClassifyDirection()
{
	// キャラクターの向きに合わせて移動ベクトルを回転
	float rotatedX = _moveVec.x * cos(Angle.y) - _moveVec.z * sin(Angle.y);
	float rotatedZ = _moveVec.x * sin(Angle.y) + _moveVec.z * cos(Angle.y);

	float angle = atan2(rotatedX, rotatedZ);

	// 45度（π/4）ごとに方向を分類
	if (angle >= -DX_PI / 8 && angle < DX_PI / 8) {
		return 0;  // 前
	}
	else if (angle >= DX_PI / 8 && angle < 3 * DX_PI / 8) {
		return 1;  // 前右
	}
	else if (angle >= 3 * DX_PI / 8 && angle < 5 * DX_PI / 8) {
		return 2;  // 右
	}
	else if (angle >= 5 * DX_PI / 8 && angle < 7 * DX_PI / 8) {
		return 3;  // 後右
	}
	else if ((angle >= 7 * DX_PI / 8 && angle <= DX_PI) || (angle < -7 * DX_PI / 8 && angle >= -DX_PI)) {
		return 4;  // 後
	}
	else if (angle >= -7 * DX_PI / 8 && angle < -5 * DX_PI / 8) {
		return 5;  // 後左
	}
	else if (angle >= -5 * DX_PI / 8 && angle < -3 * DX_PI / 8) {
		return 6;  // 左
	}
	else if (angle >= -3 * DX_PI / 8 && angle < -DX_PI / 8) {
		return 7;  // 前左
	}

	return 0;  // デフォルトは前
}

void Player::AnimationContorol()
{
	// 地面についていないとき
	if (!_isGround) {
		// ジャンプアップアニメーション出なければループアニメーションを再生する
		if (GetAnimTag() != _manager.GetConstantInt("ANIM_JUMP_UP")) {
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_JUMP_LOOP"), true, _manager.GetConstantFloat("BLEND_RATE"));
		}
		return;
	}

	if (_moveVec.x == 0.0f && _moveVec.z == 0.0f) {
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_AIMING_IDLE"), true, _manager.GetConstantFloat("BLEND_RATE"));
		return;
	}

	int dir = ClassifyDirection();

	// 走っている
	if (_runFlag) {

		// 常に走っているアニメーション
		ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
	}
	// 歩いている
	else {
		// 方向に対応するアニメーションを再生
		switch (dir) {
		case 0:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 1:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 2:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 3:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_LEFT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 4:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 5:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_FORWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 6:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));
			break;
		case 7:
			ChangeAnimation(_modelHandle, _manager.GetConstantInt("ANIM_RUN_BACKWARD_RIGHT"), true, _manager.GetConstantFloat("BLEND_RATE"));			break;
		}
	}
}

Vec3 Player::RotateBulletVec(Vec3 plPos, Vec3 cameraPos)
{

	Vec3 pos = Vec3{ plPos.x,plPos.y + 20,plPos.z };
	Vec3 ret = pos - cameraPos;

	return ret.GetNormalized();
}

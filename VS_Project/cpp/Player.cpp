#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "StageCollisionManager.h"
#include "PlayerCamera.h"

Player::Player(std::shared_ptr<StageCollisionManager>& col) :
	_MoveScaleY(0),
	_isGround(false),
	_collManager(col)
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/Player.csv");

	// 拡大の設定
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// モデルの初期処理
	InitModel(MV1LoadModel("data/model/MainActor.mv1"));

	// 座標の設定
	Position = Vec3{ 0.0f,25.0f,0.0f };

	// カプセルの初期化
	InitCapsule(Position, 4.0f, 10);

	// カメラの作成
	_pCamera = std::make_shared<PlayerCamera>(Position);
}

Player::~Player()
{
}

void Player::Update()
{
	DrawFormatString(10, 10, 0xffffff, "x:%f y:%f z:%f angleY:%f", Position.x, Position.y, Position.z, Angle.y);

	// 移動ベクトルの初期化
	_moveVec = 0;

	if (_isGround) DrawString(10, 30, "OnGround", 0xffffff);

	// xz軸方向の移動
	_moveVec += CreateMoveVec();

	// Y軸方向の移動
	_moveVec.y += CreateYMoveScale();

	// 移動ベクトルをy軸回転させる
	_moveVec = RotateVec(_moveVec, _pCamera->Angle.y);

	// 座標に移動ベクトルを足す
	Position += _moveVec;

	// 自身の回転値を更新する
	RotateAngle(_moveVec);

	// コリジョンの判定をする
	Position += _collManager->CapsuleCollision(_data);

	// カプセルに座標を渡す
	Set(Position);

	// 地上にいるか判定する
	_isGround = OnGround();

	_frontPos = Position;

	// カメラの更新
	_pCamera->Update(Position);

	// モデルの更新
	UpdateModel(GetTransformInstance());
}

void Player::Draw() const
{
#ifdef _DEBUG
	// カプセルを描画
	DrawCapsule();
#endif // DEBUG

	//DrawModel();
}

Vec3 Player::CreateMoveVec()
{
	// 移動量を返すベクトル
	Vec3 move;

	// スティックの入力値を移動ベクトルに代入する
	if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK,INPUT_PAD_1) > 3000) {
		move = Input::GetInstance().GetStickUnitVector(INPUT_LEFT_STICK, INPUT_PAD_1);
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

	if (_MoveScaleY > -1.5f) {
		_MoveScaleY -= 0.1f;
	}
	//}

	// Aボタンでジャンプ
	if (Input::GetInstance().IsHold(INPUT_A, INPUT_PAD_1) && _isGround) {

		// ジャンプ力を与える
		_MoveScaleY = 2.0f;
	}

	return _MoveScaleY;
}

bool Player::OnGround()
{
	if (_frontPos.y == Position.y) {
		return true;
	}

	return false;
}

Vec3 Player::RotateVec(Vec3 vec, float angle)
{
	// Y軸回転行列に変換
	MATRIX rotaMtx = MGetRotY(angle);

	vec = Vec3{ vec.x * -1 , vec.y,vec.z * -1 };

	// 移動ベクトルを回転値に合わせてY軸回転させる
	vec = VTransform(vec.VGet(), rotaMtx);

	return vec;
}

void Player::RotateAngle(Vec3 moveVec)
{

	float targetAngle = Angle.y;

	// 移動ベクトルが0じゃないときだけ角度を計算する
	if (moveVec.x != 0.0f && moveVec.z != 0.0f) {
		// 移動する方向の角度を求める
		Vec3 targetPos = Position + moveVec;
		float x = targetPos.x - Position.x;
		float z = targetPos.z - Position.z;
		targetAngle = atan2f(x, z);
		targetAngle = targetAngle + static_cast<float>(DX_PI);
		DX_TWO_PI;

		// 移動する方向に徐々に回転する

		// 差が移動量より小さくなったら目標の値を代入する
		if (fabsf(Angle.y - targetAngle) > GetConstantFloat("ANGLE_ROTATE_SCALE")) {
			// 増やすのと減らすのでどちらが近いか判断する
			float add = targetAngle - Angle.y;	// 足す場合の回転量
			if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// 足す場合の回転量が負の数だった場合正規化する
			float sub = static_cast<float>(DX_TWO_PI) - add;	// 引く場合の回転量

			// 回転量を比べて少ない方を選択する
			if (add < sub) {
				Angle.y += GetConstantFloat("ANGLE_ROTATE_SCALE");
			}
			else {
				Angle.y -= GetConstantFloat("ANGLE_ROTATE_SCALE");
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

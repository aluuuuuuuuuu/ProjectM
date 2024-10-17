#include "PlayerCamera.h"
#include "DxLib.h"
#include "Input.h"

PlayerCamera::PlayerCamera(Vec3 pos)
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/PlayerCamera.csv");

	// カメラのニアファーの設定
	SetCameraNearFar(GetConstantFloat("CAMERA_NEAR"), GetConstantFloat("CAMERA_FAR"));

	// 初期位置に設定する
	Position = Vec3{ pos.x + GetConstantFloat("CAMERA_BASE_POS_X"),
					 pos.y + GetConstantFloat("CAMERA_BASE_POS_Y"),
					 pos.z + GetConstantFloat("CAMERA_BASE_POS_Z"), };
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(Vec3 pos)
{
	// ターゲットの設定
	Vec3 target;
	target = Vec3(pos.x, pos.y + GetConstantFloat("CAMERA_MARGIN_Y"), pos.z);

	// 座標の設定

	SetCameraPositionAndTarget_UpVecY(Rotate(pos).VGet(), target.VGet());
}

Vec3 PlayerCamera::Rotate(Vec3 pos)
{
	// インプットのインスタンスを取得
	auto& input = Input::GetInstance();

	// 右スティックで回転
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK, INPUT_PAD_1) > GetConstantFloat("STICK_INVALID_VALUE")) {

		// スティックを傾けた方向の回転の値を増減させる
		if (input.GetStickVector(INPUT_RIGHT_STICK, INPUT_PAD_1).x != 0) {
			Angle.y += GetConstantFloat("CAMERA_ANGLE_VARIATION") * (input.GetStickThumbX(INPUT_RIGHT_STICK, INPUT_PAD_1));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK, INPUT_PAD_1).z != 0) {
			Angle.z += GetConstantFloat("CAMERA_ANGLE_VARIATION") * (input.GetStickThumbY(INPUT_RIGHT_STICK, INPUT_PAD_1));
		}

		// ラジアン角を正規化する
		Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
		if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
	}

	// 最大値と最低値を調整する
	if (Angle.z <= -GetConstantFloat("CAMERA_ANGLE_RANGE")) {
		Angle.z = -GetConstantFloat("CAMERA_ANGLE_RANGE");
	}
	else if (Angle.z >= GetConstantFloat("CAMERA_ANGLE_RANGE")) {
		Angle.z = GetConstantFloat("CAMERA_ANGLE_RANGE");
	}

	// 基準となるカメラの座標
	Vec3 basePos = VGet(GetConstantFloat("CAMERA_BASE_POS_X"),GetConstantFloat("CAMERA_BASE_POS_Y"), GetConstantFloat("CAMERA_BASE_POS_Z"));

	// カメラ座標はプレイヤー座標から変換した座標を足したところ
	return VAdd(VGet(pos.x, pos.y, pos.z), RotatePos(basePos).VGet());
}

Vec3 PlayerCamera::RotatePos(Vec3 pos)
{
	// 回転行列を作成
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);

	// 基準座標を行列で変換
	pos = VTransform(pos.VGet(), rotMtxZ);
	pos = VTransform(pos.VGet(), rotMtxX);

	return pos;
}

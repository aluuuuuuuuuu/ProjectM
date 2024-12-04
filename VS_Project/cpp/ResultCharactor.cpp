#include "ResultCharactor.h"
#include "DxLib.h"

ResultCharactor::ResultCharactor(int plNum)
{
	switch (plNum)
	{
	case 1:

		// トランスフォームの設定
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// 拡大率
		Position = Vec3{ -50,-12,0 };	// 座標
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// 角度

		// モデルの初期処理
		InitModel(MV1LoadModel("data/model/ResultCharactor1.mv1"));

		// アニメーションの初期処理
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);

		break;

	case 2:

		// トランスフォームの設定
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// 拡大率
		Position = Vec3{ -20,-13,5 };	// 座標
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// 角度

		// モデルの初期処理
		InitModel(MV1LoadModel("data/model/ResultCharactor2.mv1"));

		// アニメーションの初期処理
		InitAnimation(_modelHandle, 0, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);
		break;

	case 3:

		// トランスフォームの設定
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// 拡大率
		Position = Vec3{-10,-13,2 };	// 座標
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// 角度

		// モデルの初期処理
		InitModel(MV1LoadModel("data/model/ResultCharactor3.mv1"));

		// アニメーションの初期処理
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 0, false, 0.5f);
		break;

	case 4:

		// トランスフォームの設定
		Scale = Vec3{ 0.12f,0.12f,0.12f };	// 拡大率
		Position = Vec3{ -28,-14,3 };	// 座標
		Angle = Vec3{ 0.0f,-1.5f,0.0f };	// 角度

		// モデルの初期処理
		InitModel(MV1LoadModel("data/model/ResultCharactor4.mv1"));

		// アニメーションの初期処理
		InitAnimation(_modelHandle, 5, 0.1f);

		ChangeAnimation(_modelHandle, 1, false, 0.5f);
		break;
	default:
		break;
	}

	// カメラのニアファーのセット
	SetCameraNearFar(1.0f, 100.0f);

	// カメラの座標のセット
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(-1, 0, 0));

	// ライトの角度の調整
	SetLightDirection(VGet(-1, 0, 0));
}

ResultCharactor::~ResultCharactor()
{
}

void ResultCharactor::Update()
{

	//// アニメーションが終了している場合の処理
	//if (GetEndAnimFlag()) {

	//	// 終了したタイミングをとる
	//	if (!_flag) {
	//		_maxAnimeFlame = GetAnimeFlame();	// 最大値を保存
	//		_flag = true;
	//	}

	//	// アニメーションの増減を切り替える
	//	if (GetAnimeFlame() == _maxAnimeFlame - 3) {
	//		_animFlag = true;
	//	}
	//	else if(GetAnimeFlame() == _maxAnimeFlame) {
	//		_animFlag = false;
	//	}

	//	// フレームの増減
	//	if (_animFlag) {
	//		UpdateAnimationOnce(_modelHandle, 0.1);
	//	}
	//	else {
	//		UpdateAnimationOnce(_modelHandle, -0.1);
	//	}
	//	
	//}
	//else {
	//	UpdateAnimationOnce(_modelHandle, 0.5);
	//}

	UpdateAnimationOnce(_modelHandle, 0.5f);
	// モデルの更新処理
	UpdateModel(GetTransformInstance());
}

void ResultCharactor::Draw() const
{
	DrawModel();
}

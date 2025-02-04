#include "CreditCharacter.h"
#include "DxLib.h"

CreditCharacter::CreditCharacter(int num):
	_num(num)
{

	// 拡大の設定
	Scale = Vec3{ 0.05f,0.05f,0.05f };

	// 回転の設定
	Angle = Vec3{ 0.0f,1.5708f,0.0f };

	// プレイヤーナムに合わせてキャラをロードする
	switch (num)
	{
	case 0:
		InitModel(MV1LoadModel("data/model/DancePlayer1.mv1"));

		// 座標の設定
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 1:
		InitModel(MV1LoadModel("data/model/DancePlayer2.mv1"));

		// 座標の設定
		Position = Vec3{ 120.0f, 240.0f,  -15.0f };
		break;
	case 2:
		InitModel(MV1LoadModel("data/model/DancePlayer3.mv1"));

		// 座標の設定
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 3:
		InitModel(MV1LoadModel("data/model/DancePlayer4.mv1"));

		// 座標の設定
		Position = Vec3{ 120.0f, 240.0f, -15.0f };
		break;
	default:
		break;
	}

	InitAnimation(_modelHandle, 0, 0.5f);
	ChangeAnimation(_modelHandle, 1, true, 0.1f);


	// モデルの更新
	UpdateModel(GetTransformInstance());
}

CreditCharacter::~CreditCharacter()
{
}

void CreditCharacter::Update()
{
	// アニメーションの更新
	UpdateAnimation(_modelHandle, 0.5f);

	// モデルの更新
	UpdateModel(GetTransformInstance());
}

void CreditCharacter::Draw() const
{
	DrawModel();
}

void CreditCharacter::PosSet()
{
	switch (_num)
	{
	case 0:

		// 座標の設定
		Position = Vec3{ 120.0f, 240.0f, 15.0f };
		break;
	case 1:

		// 座標の設定
		Position = Vec3{ 120.0f, 250.0f,  -15.0f };
		break;
	case 2:

		// 座標の設定
		Position = Vec3{ 120.0f, 250.0f, 10.0f };
		break;
	case 3:
		break;
	default:
		break;
	}
}

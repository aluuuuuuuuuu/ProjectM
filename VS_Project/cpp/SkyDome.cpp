#include "SkyDome.h"
#include "DxLib.h"

SkyDome::SkyDome()
{
	// モデルの初期処理
	InitModel(MV1LoadModel("data/model/Skydome.mv1"));

	// 拡大率の設定
	Scale = Vec3{ 0.1f, 0.1f, 0.1f };

	// 座標の設定
	Position = Vec3{ 0.0f,-500.0f,0.0f };

	// 一度上の設定を反映させる
	UpdateModel(GetTransformInstance());
}

SkyDome::~SkyDome()
{
}

void SkyDome::Update()
{
	// 少しづつドームをy軸させて雲が動いてるふうに見せる
	Angle.y += 0.0001f;

	// モデルの更新処理
	UpdateModel(GetTransformInstance());
}

void SkyDome::Draw() const
{
	// 描画処理
	DrawModel();
}

#include "AnyPushButton.h"
#include "DxLib.h"
#include "SceneTitle.h"

AnyPushButton::AnyPushButton(SceneTitle& scene):
	_flame(0)
{
	// 画像のロード
	_textHandle = LoadGraph("data/image/PressAnyButton.png");
	
	// 表示位置の設定
	_dispPos = Vec2{ scene.GetConstantInt("TEXT_POS_X"),scene.GetConstantInt("TEXT_POS_Y") };
}

AnyPushButton::~AnyPushButton()
{
	DeleteGraph(_textHandle);
}

void AnyPushButton::Update()
{
	// スタート指示を点滅させる
	if (_flame == 120) {
		_flame++;
	}
	else if (_flame == 1) {
		_flame--;
	}
	else if (_flame % 2 == 0) {
		_flame += 2;
	}
	else {
		_flame -= 2;
	}
}

void AnyPushButton::Draw() const
{
	// フェードしながら描画
	int alpha = static_cast<int>(255 * ((float)_flame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// 画像の描画
	DrawRotaGraph(_dispPos.intX(), _dispPos.intY(), 1.0f, 0.0f, _textHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

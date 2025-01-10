#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"
#include "SoundManager.h"
#include "Crown.h"
#include "Logo.h"
#include "AnyPushButton.h"
#include "SceneTest.h"
#include "NumSelectButton.h"

SceneTitle::SceneTitle() :
	_flame(110)
{
	// 定数ファイルの読み込み
	ReadCSV("data/constant/SceneTitle.csv");

	// 関数ポインタの初期化
	{
		_updateFunc = &SceneTitle::FadeInUpdate;
		_drawFunc = &SceneTitle::FadeInDraw;
	}

	// 各インスタンスの作成
	{
		_pCrown = std::make_shared<Crown>(*this);	// 王冠
		_pLogo = std::make_shared <Logo>(*this);	// ロゴ
		_pText = std::make_shared<AnyPushButton>(*this);	// 文章
		_pNum = std::make_shared<NumSelectButton>(); // 人数
	}

	// 背景画像のロード
	_backgroundHandle = LoadGraph("data/image/back.jpg");

	// オープニングのテーマを再生する
	SoundManager::GetInstance().StartOp();
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_backgroundHandle);
}

void SceneTitle::Update()
{
	(this->*_updateFunc)();
}

void SceneTitle::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTitle::StartUpdate()
{
	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	// いずれかのボタンでシーン移行
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// 決定音を鳴らす
		SoundManager::GetInstance().RingStartSE();

		// フェードアウトへ移行
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::StartDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, _backgroundHandle, true);

	// ロゴの描画
	_pLogo->Draw();

	// 王冠画像の描画
	_pCrown->Draw();

	// 文章画像の描画
	_pText->Draw();
}

void SceneTitle::FadeInUpdate()
{
	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneTitle::StartUpdate;
		_drawFunc = &SceneTitle::StartDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 110) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));

		//// テスト用仮実装
		//// 初期シーンを設定
		//PlayerData data;

		//data.playerNum = 2;
		//data.charactor[0] = 1;
		//data.charactor[1] = 2;
		//SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(data));
	}
}

void SceneTitle::FadeInDraw() const
{
	StartDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::FadeOutDraw() const
{
	NumSelectDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::NumSelectUpdate()
{
	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	// 人数選択の更新処理
	_pNum->Update();

	// Aボタンが押されたら状態遷移
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeOutDraw;
	}
}

void SceneTitle::NumSelectDraw() const
{
	// 背景画像の描画
	DrawGraph(0, 0, _backgroundHandle, true);

	// ロゴの描画
	_pLogo->Draw();

	// 王冠画像の描画
	_pCrown->Draw();

	// 人数選択の描画
	_pNum->Draw();

}

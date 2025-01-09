#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"
#include "SoundManager.h"
#include "Crown.h"
#include "Logo.h"
#include "AnyPushButton.h"
#include "SceneTest.h"

SceneTitle::SceneTitle() :
	_flame(110)
{
	// 定数ファイルの読み込み
	ReadCSV("data/constant/SceneTitle.csv");

	// 関数ポインタの初期化
	{
		_updateFunc = &SceneTitle::FadeInUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}

	// 各インスタンスの作成
	{
		_pCrown = std::make_shared<Crown>(*this);	// 王冠
		_pLogo = std::make_shared <Logo>(*this);	// ロゴ
		_pText = std::make_shared<AnyPushButton>(*this);	// 文章
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

void SceneTitle::NormalUpdate()
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
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}
}

void SceneTitle::NormalDraw() const
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
		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 110) {
		//SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>());

		// テスト用仮実装
		// 初期シーンを設定
		PlayerData data;

		data.playerNum = 2;
		data.charactor[0] = 1;
		data.charactor[1] = 2;
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(data));
	}
}

void SceneTitle::FadeDraw() const
{
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

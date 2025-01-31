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
#include "FallCharactor.h"
#include "SkyDome.h"
#include "StageManager.h"
#include "TitlePlayer.h"

SceneTitle::SceneTitle(bool slidInFlag) :
	_flame(110),
	_selectDrawFlag(false)
{
	// 乱数生成器の初期化
	srand(static_cast<unsigned int>(time(nullptr)));

	// 定数ファイルの読み込み
	ReadCSV("data/constant/SceneTitle.csv");

	// カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);

	// 関数ポインタの初期化
	{
		if (slidInFlag) {
			_slidePos.x = -300;
			_updateFunc = &SceneTitle::SlideInUpdate;
			_drawFunc = &SceneTitle::SlideInDraw;
		}
		else {
			_slidePos.x = 2000;
			_updateFunc = &SceneTitle::FadeInUpdate;
			_drawFunc = &SceneTitle::FadeInDraw;
		}
	}

	// 各インスタンスの作成
	{
		_pCrown = std::make_shared<Crown>(*this);	// 王冠
		_pLogo = std::make_shared <Logo>(*this);	// ロゴ
		_pText = std::make_shared<AnyPushButton>(*this);	// 文章
		_pNum = std::make_shared<NumSelectButton>(); // 人数
		_pFallCharactor = std::make_shared<FallCharactor>(); // 落下キャラクター
		_pSkyDome = std::make_shared<SkyDome>(); // スカイドーム
		_pStage = std::make_shared<StageManager>(); // ステージマネージャ
	}

	// 両翼のモデル
	switch (rand() % 4)
	{
	case 0:
		_pModel1 = std::make_shared<TitlePlayer>(0, 0);
		_pModel2 = std::make_shared<TitlePlayer>(1, 1);
		break;
	case 1:
		_pModel1 = std::make_shared<TitlePlayer>(0, 2);
		_pModel2 = std::make_shared<TitlePlayer>(1, 3);
		break;
	case 2:
		_pModel1 = std::make_shared<TitlePlayer>(0, 0);
		_pModel2 = std::make_shared<TitlePlayer>(1, 3);
		break;
	case 3:
		_pModel1 = std::make_shared<TitlePlayer>(0, 1);
		_pModel2 = std::make_shared<TitlePlayer>(1, 2);
		break;
	default:
		break;
	}

	// スライド画像のロード
	//_slideHandle = LoadGraph("data/image/Slide.png");
	_slideHandle = LoadGraph("data/image/takasaki.png");

	// オープニングのテーマを再生する
	SoundManager::GetInstance().StartBGM(BGM_OPENING);
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_backHandle);
}

void SceneTitle::Update()
{
	(this->*_updateFunc)();
}

void SceneTitle::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTitle::NomalUpdate()
{
	// 落下キャラクターの更新処理
	_pFallCharactor->Update();

	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	// スカイドームの更新処理
	_pSkyDome->Update();

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	// いずれかのボタンが押されたら人数選択へ
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// 決定音を鳴らす
		SoundManager::GetInstance().RingSE(SE_TITLE_START);

		// 人数選択へ移行
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::NormalDraw() const
{
	// スカイドームの描画
	_pSkyDome->Draw();

	// 落下キャラクターの描画
	_pFallCharactor->Draw();

	// ロゴの描画
	_pLogo->Draw();

	// 王冠画像の描画
	_pCrown->Draw();

	// 文章画像の描画
	_pText->Draw();

	// 両翼の描画
	_pModel1->Draw();
	_pModel2->Draw();
}

void SceneTitle::SlideInUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// スライド画像の移動
	_slidePos.x += 80;

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	// 移動が終わったら通常の状態に遷移
	if (_slidePos.x >= 2000) {
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::SlideOutUpdate()
{
	// スライド画像の移動 
	_slidePos.x -= 80;

	// スカイドームの更新処理
	_pSkyDome->Update();

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	// 移動が終わったらシーン遷移
	if (_slidePos.x <= -300) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));
	}
}

void SceneTitle::SlideInDraw() const
{
	// 通常の描画も行う
	NumSelectDraw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneTitle::SlideOutDraw() const
{
	// スカイドームの描画処理
	_pSkyDome->Draw();

	// 人数選択の描画
	NumSelectDraw();

	// 両翼の描画
	_pModel1->Draw();
	_pModel2->Draw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneTitle::FadeInUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneTitle::NomalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	_flame++;
	if (_flame >= 110) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));
	}
}

void SceneTitle::FadeInDraw() const
{
	NormalDraw();

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
	// 落下キャラクターの更新処理
	_pFallCharactor->Update();

	// 王冠の更新処理
	_pCrown->Update();

	// 文章の更新処理
	_pText->Update();

	// 人数選択の更新処理
	_pNum->Update();

	// スカイドームの更新処理
	_pSkyDome->Update();

	// 両翼の更新処理
	_pModel1->Update();
	_pModel2->Update();

	// Aボタンが押されたら状態遷移
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// 決定音を鳴らす
		SoundManager::GetInstance().RingSE(SE_TITLE_START);

		_updateFunc = &SceneTitle::SlideOutUpdate;
		_drawFunc = &SceneTitle::SlideOutDraw;
	}
}

void SceneTitle::NumSelectDraw() const
{
	// スカイドームの描画
	_pSkyDome->Draw();

	// 落下キャラクターの描画
	_pFallCharactor->Draw();

	// ロゴの描画
	_pLogo->Draw();

	// 王冠画像の描画
	_pCrown->Draw();

	// 人数選択の描画
	_pNum->Draw();

	// 両翼の描画
	_pModel1->Draw();
	_pModel2->Draw();
}

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
#include "CreditCharacter.h"
#include "SceneTutorial.h"

SceneTitle::SceneTitle(bool slidInFlag) :
	_frame(110),
	_selectDrawFlag(false),
	_creditY(0),
	_creditFlame(0),
	_tutorial(false)
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

		_pChar1 = std::make_shared<CreditCharacter>(0);
		_pChar2 = std::make_shared<CreditCharacter>(1);
		_pChar3 = std::make_shared<CreditCharacter>(2);
		_pChar4 = std::make_shared<CreditCharacter>(3);
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
	_slideHandle = LoadGraph("data/image/Slide.png");

	// クレジット画像のロード
	_creditHandle = LoadGraph("data/image/Credit.png");

	// セリフ画像のロード
	_serihu = LoadGraph("data/image/message2.png");

	_serihu2 = LoadGraph("data/image/message3.png");

	//_serihu3 = LoadGraph("data/image/message4.png");

	// オープニングのテーマを再生する
	SoundManager::GetInstance().StartBGM(BGM_OPENING);

	// ライトの設定
	SetLightDirection(VECTOR{ 150.0f, 0.0f, 0.0f });
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_backHandle);
	DeleteGraph(_creditHandle);
	DeleteGraph(_serihu);
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

	// Xボタンが押されたらクレジット表示

	if (Input::GetInstance().GetPadNum() != 0) {
		for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
			if (Input::GetInstance().IsTrigger(INPUT_X, num)) {

				// フレームと座標の初期化
				_creditFlame = 0;
				_creditY = 0;

				// フェードアウト
				_updateFunc = &SceneTitle::NormalFadeOutUpdate;
				_drawFunc = &SceneTitle::NormalFadeDraw;
			}
			else if (Input::GetInstance().IsTrigger(INPUT_A, num)) {

				// 決定音を鳴らす
				SoundManager::GetInstance().RingSE(SE_TITLE_START);

				// 人数選択へ移行
				_updateFunc = &SceneTitle::NumSelectUpdate;
				_drawFunc = &SceneTitle::NumSelectDraw;
			}
		}
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

	// メッセージの描画処理
	if (Input::GetInstance().GetPadNum() == 0) {
		DrawGraph(30, 170, _serihu, true);
	}
	else {
		DrawGraph(30, 170, _serihu2, true);
	}

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
	if (_slidePos.x > 2000) {
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

	_frame--;
	if (_frame == 0) {
		_updateFunc = &SceneTitle::NormalUpdate;
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

	_frame++;
	if (_frame > 110) {
		if (_tutorial) {
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTutorial>());
		}
		else {
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));
		}
	}
}

void SceneTitle::FadeInDraw() const
{
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::FadeOutDraw() const
{
	NumSelectDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 110));
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
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {

			// 接続されているコントローラーより大きい数が選ばれたらメッセージを出す
			if (_pNum->GetSelectNum() >= Input::GetInstance().GetPadNum()) {

				// ビープ音を鳴らす
				SoundManager::GetInstance().RingSE(SE_BEEP);

				_pNum->SetMessage();
			}
			else {

				// 決定音を鳴らす
				SoundManager::GetInstance().RingSE(SE_TITLE_START);

				_updateFunc = &SceneTitle::SlideOutUpdate;
				_drawFunc = &SceneTitle::SlideOutDraw;
			}
		}

		//if (Input::GetInstance().IsTrigger(INPUT_Y, num)) {
		//	// 決定音を鳴らす
		//	SoundManager::GetInstance().RingSE(SE_TITLE_START);

		//	// チュートリアルフラグを立てる
		//	_tutorial = true;

		//	_updateFunc = &SceneTitle::FadeOutUpdate;
		//	_drawFunc = &SceneTitle::FadeOutDraw;
		//}
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

	// メッセージの描画
	DrawGraph(30, 170, _serihu3, true);

	// 両翼の描画
	_pModel1->Draw();
	_pModel2->Draw();
}

void SceneTitle::CreditUpdate()
{
	// Bボタンが押されたら通常の処理に移行
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {

			// 通常の処理に移行
			_updateFunc = &SceneTitle::CreditFadeOutUpdate;
			_drawFunc = &SceneTitle::CreditFadeDraw;
		}
	}

	// フレームの加算
	_creditFlame++;

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// クレジット座標の移動
			_creditY--;
		}
	}

	// BGMが終わったら通常の処理に戻る
	if (_creditFlame == 3960) {
		// BGMを変える
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		// 通常の処理に移行
		_updateFunc = &SceneTitle::CreditFadeOutUpdate;
		_drawFunc = &SceneTitle::CreditFadeDraw;
	}

	if (_creditFlame == 2500) {
		_pChar1->PosSet();
		_pChar2->PosSet();
		_pChar3->PosSet();
		_pChar4->PosSet();
	}

	// モデルの更新
	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();
}

void SceneTitle::CreditDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);

	if (_creditFlame < 600) {
		_pChar1->Draw();
	}
	else if (_creditFlame < 1800) {
		_pChar2->Draw();
	}
	else if (_creditFlame < 2400) {
		_pChar3->Draw();
	}
	else if (_creditFlame < 3000) {
		_pChar4->Draw();
	}
	else {
		_pChar1->Draw();
		_pChar2->Draw();
		_pChar3->Draw();
		_pChar4->Draw();
	}

}

void SceneTitle::NormalFadeInUpdate()
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

	_frame--;
	if (_frame == 0) {

		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::NormalFadeOutUpdate()
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

	_frame++;
	if (_frame == 60) {
		SoundManager::GetInstance().StopBGM(BGM_OPENING);
		SoundManager::GetInstance().StartBGM(BGM_THEME);

		_updateFunc = &SceneTitle::CreditFadeInUpdate;
		_drawFunc = &SceneTitle::CreditFadeDraw;
	}
}

void SceneTitle::NormalFadeDraw() const
{
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::CreditFadeInUpdate()
{
	// フレームの加算
	_creditFlame++;

	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// クレジット座標の移動
			_creditY--;
		}
	}

	_frame--;
	if (_frame == 0) {

		_updateFunc = &SceneTitle::CreditUpdate;
		_drawFunc = &SceneTitle::CreditDraw;
	}


}

void SceneTitle::CreditFadeOutUpdate()
{
	// フレームの加算
	_creditFlame++;

	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// クレジット座標の移動
			_creditY--;
		}
	}

	_frame++;
	if (_frame == 60) {
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		_updateFunc = &SceneTitle::NormalFadeInUpdate;
		_drawFunc = &SceneTitle::NormalFadeDraw;
	}
}

void SceneTitle::CreditFadeDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);

	if (_creditFlame < 600) {
		_pChar1->Draw();
	}
	else if (_creditFlame < 1800) {
		_pChar2->Draw();
	}
	else if (_creditFlame < 2400) {
		_pChar3->Draw();
	}
	else if (_creditFlame < 3000) {
		_pChar4->Draw();
	}
	else {
		_pChar1->Draw();
		_pChar2->Draw();
		_pChar3->Draw();
		_pChar4->Draw();
	}

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

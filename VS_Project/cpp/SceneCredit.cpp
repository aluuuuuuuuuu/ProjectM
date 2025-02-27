#include "SceneCredit.h"
#include "DxLib.h"
#include "CreditCharacter.h"
#include "SoundManager.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"

SceneCredit::SceneCredit():
	_frame(60),
	_creditY(0),
	_creditFlame(0)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneCredit::FadeInUpdate;
	_drawFunc = &SceneCredit::FadeDraw;

	// モデルのインスタンスの作成
	_pChar1 = std::make_shared<CreditCharacter>(0);
	_pChar2 = std::make_shared<CreditCharacter>(1);
	_pChar3 = std::make_shared<CreditCharacter>(2);
	_pChar4 = std::make_shared<CreditCharacter>(3);

	// クレジット画像のロード
	_creditHandle = LoadGraph("data/image/Credit.png");

	// BGMの変更
	SoundManager::GetInstance().StopBGM(BGM_OPENING);
	SoundManager::GetInstance().StartBGM(BGM_THEME);
}

SceneCredit::~SceneCredit()
{
	DeleteGraph(_creditHandle);
}

void SceneCredit::Update()
{
	(this->*_updateFunc)();
}

void SceneCredit::Draw() const
{
	(this->*_drawFunc)();
}

void SceneCredit::NormalUpdate()
{

	// Bボタンが押されたらタイトルシーンに切り替え
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {

			// フェードアウトに移行
			_updateFunc = &SceneCredit::FadeOutUpdate;
			_drawFunc = &SceneCredit::FadeDraw;
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

		// フェードアウトに移行
		_updateFunc = &SceneCredit::FadeOutUpdate;
		_drawFunc = &SceneCredit::FadeDraw;
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

void SceneCredit::NormalDraw() const
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

void SceneCredit::FadeInUpdate()
{
	// フレームの加算
	_creditFlame++;

	// キャラクターの更新処理
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

		_updateFunc = &SceneCredit::NormalUpdate;
		_drawFunc = &SceneCredit::NormalDraw;
	}
}

void SceneCredit::FadeOutUpdate()
{
	// フレームの加算
	_creditFlame++;

	// キャラクターの更新処理
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

		// タイトルシーンに切り替え
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(false));
	}
}

void SceneCredit::FadeDraw() const
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

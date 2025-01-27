#include "SceneSelect.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharacterCard.h"
#include "CharacterSelectManager.h"
#include "SelectUI.h"
#include "SceneTitle.h"
#include "SoundManager.h"
#include "SkyDome.h"
#include "ScenePvp.h"
#include "ScenePve.h"

SceneSelect::SceneSelect(int num) :
	_flame(60)
{
	// 関数ポインタの初期化
	_updateFunc = &SceneSelect::SlideInUpdate;
	_drawFunc = &SceneSelect::SlideInDraw;

	// プレイヤーデータの初期化
	for (auto& pl : _plData.character) {
		pl = -1;
	}
	_plData.playerNum = num;

	// インスタンスの作成
	{
		_pSelectManager = std::make_shared<CharacterSelectManager>(_plData);	// セレクトマネージャー
		_pUi = std::make_shared<SelectUI>();	// ui
		_pSkyDome = std::make_shared<SkyDome>();	// スカイドーム
	}

	// スライド画像のロード
	_slideHandle = LoadGraph("data/image/Slide.png");

	_slidePos = Vec2{ -300,0 };
}

SceneSelect::~SceneSelect()
{
	DeleteGraph(_slideHandle);
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::CharacterSelectUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// セレクトマネージャーの更新
	_pSelectManager->Update();

	// スタートボタンが押されたらゲームシーンに移行する
	if (_pSelectManager->GetStart()) {

		// プレイヤーデータを作成する
		_pSelectManager->CreateData();

		// フェードアウトに移行
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}

	// マネージャーの戻るフラグが立っていたら人数選択に戻る
	if (_pSelectManager->GetReturnFlag()) {

		// キャンセル音を鳴らす
		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// フェードアウトに移行
		_updateFunc = &SceneSelect::SlideOutUpdate;
		_drawFunc = &SceneSelect::SlideOutDraw;
	}
}

void SceneSelect::CharacterSelectDraw() const
{
	// スカイドームの描画
	_pSkyDome->Draw();

	// uiの描画
	_pUi->Draw();

	// セレクトマネージャーの描画処理
	_pSelectManager->Draw();
}

void SceneSelect::SlideInUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// スライド画像の移動
	_slidePos.x -= 80;
	if (_slidePos.x <= -3840) {
		_updateFunc = &SceneSelect::CharacterSelectUpdate;
		_drawFunc = &SceneSelect::CharacterSelectDraw;
	}
}

void SceneSelect::SlideInDraw() const
{
	// 通常の描画も行う
	CharacterSelectDraw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelect::SlideOutUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	_slidePos.x += 80;
	if (_slidePos.x >= -300) {
		// 次のシーンに移行する
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(true));
	}
}

void SceneSelect::SlideOutDraw() const
{
	// 通常の描画も行う
	CharacterSelectDraw();

	// スライド画像の描画
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelect::FadeOutUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	_flame++;
	if (_flame >= 60) {

		// 次のシーンに移行する
		if (_plData.playerNum == PLAYER_ONE) {
			_plData.aiFlag = true;
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePve>(_plData));
		}
		else {
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePvp>(_plData));
		}
	}
}

void SceneSelect::FadeOutDraw() const
{
	// 通常の描画も行う
	CharacterSelectDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

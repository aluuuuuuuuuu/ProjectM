#include "TutorialManager.h"
#include "BulletManager.h"
#include "StageManager.h"
#include "MapBulletCollisionManager.h"
#include "StageCollisionManager.h"
#include "PlayerManager.h"
#include "SkyDome.h"
#include "WedgewormManager.h"
#include "EffectManager.h"
#include "Input.h"

TutorialManager::TutorialManager() :
	_frame(0),
	_tutorialProgress(GUIDE_CAMERA),
	_endFrag(false)
{
	PlayerData data;

	data.aiFlag = false;
	data.character[PLAYER_ONE] = 0;
	data.playerNum = PLAYER_ONE;

	// 各クラスのインスタンス作成
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// 禊虫マネージャ
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);	// バレットマネージャー
		_pStage = std::make_shared<StageManager>();													// ステージマネージャー
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// バレットコリジョンマネージャー
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// ステージコリジョンマネージャー
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// プレイヤーマネージャー
		_pSkyDome = std::make_shared<SkyDome>();	// スカイドーム
	}

	// ライトの設定
	{
		// ライティングを使用する
		SetUseLighting(true);

		// ライトのカラーを調整する
		SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

		// ライトの角度を設定
		SetLightDirection(VECTOR{ 1.0f, -1.0f ,0.0f, });
	}

	// 画像のロード
	{
		// ガイド文章の画像のロード
		_guideHandle[GUIDE_CAMERA] = LoadGraph("data/image/GuideCamera.png");
		_guideHandle[GUIDE_MOVE] = LoadGraph("data/image/GuideMove.png");
		_guideHandle[GUIDE_JUMP] = LoadGraph("data/image/GuideJump.png");
		_guideHandle[GUIDE_SHOT] = LoadGraph("data/image/GuideShot.png");

		// クリア画像のロード
		_clearHandle = LoadGraph("data/image/Clear.png");
	}

	// ガイド文章の座標の設定
	_guidePos = Vec2{ 1920 / 2, 200 };

	// クリア画像の座標の設定
	_clearPos = Vec2{ 1920 / 2, 1080 / 2 };

	// 関数ポインタの初期化
	_updateFunc = &TutorialManager::CameraUpdate;
	_drawFunc = &TutorialManager::ShareDraw;

	// 禊虫の更新
	_pWedgewormManager->Update();

	// プレイヤーの更新処理
	_pPlayerManager->Update();
}

TutorialManager::~TutorialManager()
{
	// ガイド文章の削除
	for (int i = 0; i < 5; i++) {
		DeleteGraph(_guideHandle[i]);
	}
}

void TutorialManager::Update()
{
	// デフォルトの処理
	DefaultUpdate();

	(this->*_updateFunc)();
}

void TutorialManager::Draw() const
{
	(this->*_drawFunc)();
}

void TutorialManager::CameraUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// チュートリアルを進める
			_updateFunc = &TutorialManager::MoveUpdate;
			_tutorialProgress++;
		}
	}
	// カメラ操作が１秒以上行われたらクリア処理を行う
	else if(Input::GetInstance().GetStickVectorLength(INPUT_RIGHT_STICK, INPUT_PAD_1) > 5000.0f){

		_frame++;
		if (_frame > 60) {
			_endFrag = true;
			_frame = 0;
			_clearScale = 10.0;
		}
	}
}

void TutorialManager::MoveUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// チュートリアルを進める
			_updateFunc = &TutorialManager::JumpUpdate;
			_tutorialProgress++;
		}
	}
	// 移動操作が１ち秒以上行われたらクリア処理を行う
	else if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > 5000.0f) {

		_frame++;
		if (_frame > 60) {
			_endFrag = true;
			_frame = 0;
			_clearScale = 10.0;
		}
	}
}

void TutorialManager::JumpUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// チュートリアルを進める
			_updateFunc = &TutorialManager::ShotUpdate;
			_tutorialProgress++;
		}
	}
	// ジャンプ操作が一回以上行われたらクリア処理を行う
	else if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
}

void TutorialManager::ShotUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// チュートリアルを進める
			_updateFunc = &TutorialManager::SelectUpdate;
			_tutorialProgress++;
		}
	}
	// ジャンプ操作が一回以上行われたらクリア処理を行う
	else if (Input::GetInstance().IsTrigger(INPUT_X, INPUT_PAD_1) || Input::GetInstance().IsTrigger(INPUT_RIGHT_TRIGGER, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
}

void TutorialManager::SelectUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// チュートリアルを進める
			_updateFunc = &TutorialManager::LastUpdate;
			_tutorialProgress++;
		}
	}
	// ジャンプ操作が一回以上行われたらクリア処理を行う
	else if (Input::GetInstance().IsTrigger(INPUT_RIGHT_SHOULDER, INPUT_PAD_1) || Input::GetInstance().IsTrigger(INPUT_LEFT_SHOULDER, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
}

void TutorialManager::LastUpdate()
{
}

void TutorialManager::ShareDraw() const
{
	// カメラの設定
	_pPlayerManager->CameraSet(0);

	//スカイドームの描画
	_pSkyDome->Draw();

	// バレットの描画
	_pBulletManager->Draw();

	// ステージの描画
	_pStage->DrawStage();

	// 禊虫の描画
	_pWedgewormManager->Draw();

	// エフェクトの描画
	EffectManager::GetInstance().Draw();

	// プレイヤーの描画
	_pPlayerManager->Draw(0);

	// ガイド文章の描画
	DrawRotaGraph(_guidePos.intX(), _guidePos.intY(), 1.0, 0.0, _guideHandle[_tutorialProgress], true);

	// クリア画像の描画
	if (_endFrag) DrawRotaGraph(_clearPos.intX(), _clearPos.intY(), _clearScale, 0.0, _clearHandle, true);
}

bool TutorialManager::ClearFunction()
{
	_clearScale -= 0.5;

	_clearScale = max(1.0, _clearScale);

	// Aボタンが押されたらtrueを返す
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1) && _clearScale >= 1.0) {
		return true;
	}
}

void TutorialManager::DefaultUpdate()
{
	// スカイドームの更新処理
	_pSkyDome->Update();

	// プレイヤーの更新処理
	_pPlayerManager->Update();

	// バレットの更新
	_pBulletManager->Update();

	// 禊虫の更新
	_pWedgewormManager->Update();
}

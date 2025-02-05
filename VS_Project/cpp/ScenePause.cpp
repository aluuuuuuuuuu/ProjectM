#include "ScenePause.h"]
#include "SceneManager.h"
#include "DxLib.h"
#include "ScenePve.h"
#include "ScenePvp.h"
#include "Input.h"

ScenePause::ScenePause(PlayerData data):
	_data(data),
	_frame(60),
	_textFrame(0)
{
	_graph = LoadGraph("data/image/Pause.png");
	_text = LoadGraph("data/image/PressAnyButton.png");

	_updateFunc = &ScenePause::FadeInUpdate;
	_drawFunc = &ScenePause::FadeDraw;
}

ScenePause::~ScenePause()
{
	DeleteGraph(_graph);
	DeleteGraph(_text);
}

void ScenePause::Update()
{
	(this->*_updateFunc)();
}

void ScenePause::Draw() const
{
	(this->*_drawFunc)();
}

void ScenePause::NormalUpdate()
{
	for (int num = 0; num <= _data.playerNum; num++) {
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {
			_updateFunc = &ScenePause::FadeOutUpdate;
			_drawFunc = &ScenePause::FadeDraw;
		}
	}

	// スタート指示を点滅させる
	if (_textFrame == 120) {
		_textFrame++;
	}
	else if (_textFrame == 1) {
		_textFrame--;
	}
	else if (_textFrame % 2 == 0) {
		_textFrame += 2;
	}
	else {
		_textFrame -= 2;
	}
}

void ScenePause::NormalDraw() const
{
	DrawGraph(0, 0, _graph, true);

	// フェードしながら描画
	int alpha = static_cast<int>(255 * ((float)_textFrame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// 画像の描画
	DrawRotaGraph(960, 945, 1.0f, 0.0f, _text, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScenePause::FadeInUpdate()
{
	NormalUpdate();

	_frame--;
	if (_frame == 0) {
		_updateFunc = &ScenePause::NormalUpdate;
		_drawFunc = &ScenePause::NormalDraw;
	}
}

void ScenePause::FadeOutUpdate()
{
	NormalUpdate();

	_frame++;
	if (_frame > 60) {
		// 次のシーンに移行する
		if (_data.playerNum == PLAYER_ONE) {
			_data.aiFlag = true;
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePve>(_data));
		}
		else {
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePvp>(_data));
		}
	}
}

void ScenePause::FadeDraw() const
{
	// 通常の描画
	NormalDraw();

	//フェード暗幕
	int alpha = static_cast<int>(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

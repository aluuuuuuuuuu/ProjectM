#include "ScenePause.h"]
#include "SceneManager.h"
#include "DxLib.h"
#include "ScenePve.h"
#include "ScenePvp.h"
#include "Input.h"
#include "Application.h"

ScenePause::ScenePause(PlayerData data) :
	_data(data),
	_frame(Application::GetInstance().GetConstantInt("FRAME_NUM")),
	_textFrame(0)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/ScenePause.csv");

	// �摜�̃��[�h
	_graphHandle = LoadGraph("data/image/Pause.png");
	_textImageHandle = LoadGraph("data/image/PressAnyButton.png");

	_updateFunc = &ScenePause::FadeInUpdate;
	_drawFunc = &ScenePause::FadeDraw;
}

ScenePause::~ScenePause()
{
	DeleteGraph(_graphHandle);
	DeleteGraph(_textImageHandle);
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

	// �X�^�[�g�w����_�ł�����
	if (_textFrame == Application::GetInstance().GetConstantInt("FRAME_NUM") * 2) {
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
	// ��������摜�̕`��
	DrawGraph(0, 0, _graphHandle, true);

	// �t�F�[�h���Ȃ���`��
	int alpha = static_cast<int>(255 * ((float)_textFrame / Application::GetInstance().GetConstantInt("FRAME_NUM") * 2));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	// ���̃e�L�X�g�摜�̕`��
	DrawRotaGraph(GetConstantInt("IMAGE_DRAW_X"), GetConstantInt("IMAGE_DRAW_Y"), 1.0f, 0.0f, _textImageHandle, true);
	
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
	if (_frame > Application::GetInstance().GetConstantInt("FRAME_NUM")) {
		// ���̃V�[���Ɉڍs����
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
	// �ʏ�̕`��
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM")));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

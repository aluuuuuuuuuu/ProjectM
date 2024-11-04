#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneSelect.h"
#include "Application.h"
#include "SoundManager.h"
#include "Crown.h"

SceneTitle::SceneTitle() :
	_flame(110)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneTitle::FadeInUpdate;
	_drawFunc = &SceneTitle::FadeDraw;

	// �����C���X�^���X�̍쐬
	_pCrown = std::make_shared<Crown>();

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(1, 512);

	// �^�C�g�����S�̃��[�h
	_logoHandle = LoadGraph("data/image/TitleLogo.png");

	// anybutton�摜�̃��[�h
	_guideHandle = LoadGraph("data/image/PressAnyButton.png");

	// ��ʃT�C�Y���擾
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");

	// �w�i�摜�̃��[�h
	_backgroundHandle = LoadGraph("data/image/back.jpg");

	// �I�[�v�j���O�̃e�[�}���Đ�����
	SoundManager::GetInstance().StartOp();
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_logoHandle);
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
	// �����̍X�V����
	_pCrown->Update();

	// �����ꂩ�̃{�^���ŃV�[���ڍs
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// ���艹��炷
		SoundManager::GetInstance().RingStartSE();

		// �t�F�[�h�A�E�g�ֈڍs
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}

	// �X�^�[�g�w����_�ł�����
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

void SceneTitle::NormalDraw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, _backgroundHandle, true);

	// ���S�̕`��
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 5 * 2, 1.0f, 0.0f, _logoHandle, true, false);

	// �����摜�̕`��
	_pCrown->Draw();

	int alpha = (int)(255 * ((float)_flame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(_windowWidth / 2, _windowHeight / 8 * 7, 1.0f, 0.0f, _guideHandle, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>());
	}
}

void SceneTitle::FadeDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

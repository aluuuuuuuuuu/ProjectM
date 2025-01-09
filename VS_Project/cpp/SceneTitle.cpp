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
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/SceneTitle.csv");

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &SceneTitle::FadeInUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}

	// �e�C���X�^���X�̍쐬
	{
		_pCrown = std::make_shared<Crown>(*this);	// ����
		_pLogo = std::make_shared <Logo>(*this);	// ���S
		_pText = std::make_shared<AnyPushButton>(*this);	// ����
	}

	// �w�i�摜�̃��[�h
	_backgroundHandle = LoadGraph("data/image/back.jpg");

	// �I�[�v�j���O�̃e�[�}���Đ�����
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
	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	// �����ꂩ�̃{�^���ŃV�[���ڍs
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// ���艹��炷
		SoundManager::GetInstance().RingStartSE();

		// �t�F�[�h�A�E�g�ֈڍs
		_updateFunc = &SceneTitle::FadeOutUpdate;
		_drawFunc = &SceneTitle::FadeDraw;
	}
}

void SceneTitle::NormalDraw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, _backgroundHandle, true);

	// ���S�̕`��
	_pLogo->Draw();

	// �����摜�̕`��
	_pCrown->Draw();

	// ���͉摜�̕`��
	_pText->Draw();
}

void SceneTitle::FadeInUpdate()
{
	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
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

		// �e�X�g�p������
		// �����V�[����ݒ�
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

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

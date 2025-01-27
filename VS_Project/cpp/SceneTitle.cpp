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

SceneTitle::SceneTitle(bool slidInFlag):
	_flame(110),
	_selectDrawFlag(false)
{
	// ����������̏�����
	srand(static_cast<unsigned int>(time(nullptr)));

	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/SceneTitle.csv");

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{150.0f, 250.0f, 0.0f });

	// �֐��|�C���^�̏�����
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

	// �e�C���X�^���X�̍쐬
	{
		_pCrown = std::make_shared<Crown>(*this);	// ����
		_pLogo = std::make_shared <Logo>(*this);	// ���S
		_pText = std::make_shared<AnyPushButton>(*this);	// ����
		_pNum = std::make_shared<NumSelectButton>(); // �l��
		_pFallCharactor = std::make_shared<FallCharactor>(); // �����L�����N�^�[
		_pSkyDome = std::make_shared<SkyDome>(); // �X�J�C�h�[��
		_pStage = std::make_shared<StageManager>(); // �X�e�[�W�}�l�[�W��
	}

	// �w�i�摜�̃��[�h

	switch (rand() % 4)
	{
	case 0:
		_backHandle = LoadGraph("data/image/taitkeBack1.png");
		break;
	case 1:
		_backHandle = LoadGraph("data/image/taitkeBack2.png");
		break;
	case 2:
		_backHandle = LoadGraph("data/image/taitkeBack3.png");
		break;
	case 3:
		_backHandle = LoadGraph("data/image/taitkeBack4.png");
		break;
	default:
		break;
	}



	// �X���C�h�摜�̃��[�h
	_slideHandle = LoadGraph("data/image/Slide.png");

	// �I�[�v�j���O�̃e�[�}���Đ�����
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
	// �����L�����N�^�[�̍X�V����
	_pFallCharactor->Update();

	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �����ꂩ�̃{�^���������ꂽ��l���I����
	if (Input::GetInstance().AnyPressButton(INPUT_PAD_1)) {

		// ���艹��炷
		SoundManager::GetInstance().RingSE(SE_TITLE_START);

		// �l���I���ֈڍs
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::NormalDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// �����L�����N�^�[�̕`��
	_pFallCharactor->Draw();

	// �w�i�摜�̕`��
	DrawGraph(0, 0, _backHandle, true);

	// ���S�̕`��
	_pLogo->Draw();

	// �����摜�̕`��
	_pCrown->Draw();

	// ���͉摜�̕`��
	_pText->Draw();
}

void SceneTitle::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �X���C�h�摜�̈ړ�
	_slidePos.x += 80;

	// �ړ����I�������ʏ�̏�ԂɑJ��
	if (_slidePos.x >= 2000) {
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::SlideOutUpdate()
{
	// �X���C�h�摜�̈ړ� 
	_slidePos.x -= 80;

	// �ړ����I�������V�[���J��
	if (_slidePos.x <= -300) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));
	}
}

void SceneTitle::SlideInDraw() const
{
	// �ʏ�̕`����s��
	NumSelectDraw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneTitle::SlideOutDraw() const
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �l���I���̕`��
	NumSelectDraw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneTitle::FadeInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();


	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneTitle::NomalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 110) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pNum->GetSelectNum()));
	}
}

void SceneTitle::FadeInDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::FadeOutDraw() const
{
	NumSelectDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::NumSelectUpdate()
{
	// �����L�����N�^�[�̍X�V����
	_pFallCharactor->Update();

	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	// �l���I���̍X�V����
	_pNum->Update();

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// A�{�^���������ꂽ���ԑJ��
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// ���艹��炷
		SoundManager::GetInstance().RingSE(SE_TITLE_START);

		_updateFunc = &SceneTitle::SlideOutUpdate;
		_drawFunc = &SceneTitle::SlideOutDraw;
	}
}

void SceneTitle::NumSelectDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// �����L�����N�^�[�̕`��
	_pFallCharactor->Draw();

	// �w�i�摜�̕`��
	DrawGraph(0, 0, _backHandle, true);

	// ���S�̕`��
	_pLogo->Draw();

	// �����摜�̕`��
	_pCrown->Draw();

	// �l���I���̕`��
	_pNum->Draw();

}

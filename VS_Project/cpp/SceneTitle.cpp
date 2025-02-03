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
	_selectDrawFlag(false),
	_creditY(0),
	_creditFlame(0)
{
	// ����������̏�����
	srand(static_cast<unsigned int>(time(nullptr)));

	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/SceneTitle.csv");

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);

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

	// �����̃��f��
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

	// �X���C�h�摜�̃��[�h
	//_slideHandle = LoadGraph("data/image/Slide.png");
	_slideHandle = LoadGraph("data/image/takasaki.png");

	// �N���W�b�g�摜�̃��[�h
	_creditHandle = LoadGraph("data/image/Credit.png");

	// �Z���t�摜�̃��[�h
	_serihu = LoadGraph("data/image/message2.png");

	_serihu2 = LoadGraph("data/image/message3.png");

	// �I�[�v�j���O�̃e�[�}���Đ�����
	SoundManager::GetInstance().StartBGM(BGM_OPENING);

	// ���C�g�̐ݒ�
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

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	// X�{�^���������ꂽ��N���W�b�g�\��

	if (Input::GetInstance().GetPadNum() != 0) {
		for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
			if (Input::GetInstance().IsTrigger(INPUT_X, num)) {

				// �t���[���ƍ��W�̏�����
				_creditFlame = 0;
				_creditY = 0;

				// �t�F�[�h�A�E�g
				_updateFunc = &SceneTitle::NormalFadeOutUpdate;
				_drawFunc = &SceneTitle::NormalFadeDraw;
			}
			else if (Input::GetInstance().IsTrigger(INPUT_A, num)) {

				// ���艹��炷
				SoundManager::GetInstance().RingSE(SE_TITLE_START);

				// �l���I���ֈڍs
				_updateFunc = &SceneTitle::NumSelectUpdate;
				_drawFunc = &SceneTitle::NumSelectDraw;
			}
		}
	}
}

void SceneTitle::NormalDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// �����L�����N�^�[�̕`��
	_pFallCharactor->Draw();

	// ���S�̕`��
	_pLogo->Draw();

	// �����摜�̕`��
	_pCrown->Draw();

	// ���͉摜�̕`��
	_pText->Draw();

	// ���b�Z�[�W�̕`�揈��
	if (Input::GetInstance().GetPadNum() == 0) {
		DrawGraph(30, 170, _serihu, true);
	}
	else {
		DrawGraph(30, 170, _serihu2, true);
	}

	// �����̕`��
	_pModel1->Draw();
	_pModel2->Draw();
}

void SceneTitle::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �X���C�h�摜�̈ړ�
	_slidePos.x += 80;

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	// �ړ����I�������ʏ�̏�ԂɑJ��
	if (_slidePos.x > 2000) {
		_updateFunc = &SceneTitle::NumSelectUpdate;
		_drawFunc = &SceneTitle::NumSelectDraw;
	}
}

void SceneTitle::SlideOutUpdate()
{
	// �X���C�h�摜�̈ړ� 
	_slidePos.x -= 80;

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

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
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// �l���I���̕`��
	NumSelectDraw();

	// �����̕`��
	_pModel1->Draw();
	_pModel2->Draw();

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

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	_flame--;
	if (_flame == 0) {
		_updateFunc = &SceneTitle::NomalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	_flame++;
	if (_flame > 110) {
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

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	// A�{�^���������ꂽ���ԑJ��
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {

			// �ڑ�����Ă���R���g���[���[���傫�������I�΂ꂽ�烁�b�Z�[�W���o��
			if (_pNum->GetSelectNum() >= Input::GetInstance().GetPadNum()) {

				// �r�[�v����炷
				SoundManager::GetInstance().RingSE(SE_BEEP);

				_pNum->SetMessage();
			}
			else {

				// ���艹��炷
				SoundManager::GetInstance().RingSE(SE_TITLE_START);

				_updateFunc = &SceneTitle::SlideOutUpdate;
				_drawFunc = &SceneTitle::SlideOutDraw;
			}
		}
	}
}

void SceneTitle::NumSelectDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// �����L�����N�^�[�̕`��
	_pFallCharactor->Draw();

	// ���S�̕`��
	_pLogo->Draw();

	// �����摜�̕`��
	_pCrown->Draw();

	// �l���I���̕`��
	_pNum->Draw();

	// �����̕`��
	_pModel1->Draw();
	_pModel2->Draw();
}

void SceneTitle::CreditUpdate()
{
	// B�{�^���������ꂽ��ʏ�̏����Ɉڍs
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {

			// �ʏ�̏����Ɉڍs
			_updateFunc = &SceneTitle::CreditFadeOutUpdate;
			_drawFunc = &SceneTitle::CreditFadeDraw;
		}
	}

	// �t���[���̉��Z
	_creditFlame++;

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// �N���W�b�g���W�̈ړ�
			_creditY--;
		}
	}

	// BGM���I�������ʏ�̏����ɖ߂�
	if (_creditFlame == 3960) {
		// BGM��ς���
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		// �ʏ�̏����Ɉڍs
		_updateFunc = &SceneTitle::CreditFadeOutUpdate;
		_drawFunc = &SceneTitle::CreditFadeDraw;
	}
}

void SceneTitle::CreditDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);
}

void SceneTitle::NormalFadeInUpdate()
{
	// �����L�����N�^�[�̍X�V����
	_pFallCharactor->Update();

	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	_flame--;
	if (_flame == 0) {

		_updateFunc = &SceneTitle::NomalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::NormalFadeOutUpdate()
{
	// �����L�����N�^�[�̍X�V����
	_pFallCharactor->Update();

	// �����̍X�V����
	_pCrown->Update();

	// ���͂̍X�V����
	_pText->Update();

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	_flame++;
	if (_flame == 60) {
		SoundManager::GetInstance().StopBGM(BGM_OPENING);
		SoundManager::GetInstance().StartBGM(BGM_THEME);

		_updateFunc = &SceneTitle::CreditFadeInUpdate;
		_drawFunc = &SceneTitle::CreditFadeDraw;
	}
}

void SceneTitle::NormalFadeDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::CreditFadeInUpdate()
{
	// �t���[���̉��Z
	_creditFlame++;

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// �N���W�b�g���W�̈ړ�
			_creditY--;
		}
	}

	_flame--;
	if (_flame == 0) {

		_updateFunc = &SceneTitle::CreditUpdate;
		_drawFunc = &SceneTitle::CreditDraw;
	}
}

void SceneTitle::CreditFadeOutUpdate()
{
	// �t���[���̉��Z
	_creditFlame++;

	if (_creditFlame > 600) {
		if (_creditY > -3500 + 1080) {
			// �N���W�b�g���W�̈ړ�
			_creditY--;
		}
	}

	_flame++;
	if (_flame == 60) {
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		_updateFunc = &SceneTitle::NormalFadeInUpdate;
		_drawFunc = &SceneTitle::NormalFadeDraw;
	}
}

void SceneTitle::CreditFadeDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

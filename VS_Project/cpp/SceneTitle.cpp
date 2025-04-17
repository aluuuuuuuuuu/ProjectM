#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "SoundManager.h"
#include "Crown.h"
#include "Logo.h"
#include "AnyPushButton.h"
#include "FallCharactor.h"
#include "SkyDome.h"
#include "TitlePlayer.h"
#include "SceneSelectMode.h"
#include "SceneCredit.h"
#include "Application.h"

SceneTitle::SceneTitle(bool slidInFlag) :
	_frame(Application::GetInstance().GetConstantInt("FRAME_NUM")),
	_selectDrawFlag(false),
	_endFrag(false)
{
	// ����������̏�����
	srand(static_cast<unsigned int>(time(nullptr)));

	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/SceneTitle.csv");

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ GetConstantFloat("CAMERA_POS_X"),GetConstantFloat("CAMERA_POS_Y"),GetConstantFloat("CAMERA_POS_Z") },
		VECTOR{ GetConstantFloat("CAMERA_TARGET_X"), GetConstantFloat("CAMERA_TARGET_Y"), GetConstantFloat("CAMERA_TARGET_Z") });

	SetCameraNearFar(GetConstantFloat("CAMERA_NEAR"), GetConstantFloat("CAMERA_FAR"));

	// �֐��|�C���^�̏�����
	{
		if (slidInFlag) {
			_slidePos.x = GetConstantInt("SLIDE_MOVE_SCALE");
			_updateFunc = &SceneTitle::SlideInUpdate;
			_drawFunc = &SceneTitle::SlideInDraw;
		}
		else {
			_slidePos.x = GetConstantInt("SLIDE_IN_START_X");
			_updateFunc = &SceneTitle::FadeInUpdate;
			_drawFunc = &SceneTitle::FadeInDraw;
		}
	}

	// �e�C���X�^���X�̍쐬
	{
		_pCrown = std::make_shared<Crown>(*this);	// ����
		_pLogo = std::make_shared <Logo>(*this);	// ���S
		_pText = std::make_shared<AnyPushButton>(*this);	// ����
		_pFallCharactor = std::make_shared<FallCharactor>(); // �����L�����N�^�[
		_pSkyDome = std::make_shared<SkyDome>(); // �X�J�C�h�[��
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
	_slideHandle = LoadGraph("data/image/Slide.png");

	// �Z���t�摜�̃��[�h
	_serihu = LoadGraph("data/image/message2.png");

	_serihu2 = LoadGraph("data/image/message3.png");

	_serihu3 = LoadGraph("data/image/message4.png");

	// �Q�[���I���摜�̃��[�h
	_endHandle = LoadGraph("data/image/GameEnda.png");

	// �Q�[���I���{�^���e�L�X�g�摜
	_gameEndHandle = LoadGraph("data/image/startToGameEnd.png");

	// �I�[�v�j���O�̃e�[�}���Đ�����
	SoundManager::GetInstance().StopBGM(BGM_THEME);
	SoundManager::GetInstance().StartBGM(BGM_OPENING);

	// ���C�g�̐ݒ�
	SetLightDirection(VECTOR{ 150.0f, 0.0f, 0.0f });
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(_serihu);
	DeleteGraph(_serihu2);
	DeleteGraph(_serihu3);
	DeleteGraph(_slideHandle);
	DeleteGraph(_endHandle);
	DeleteGraph(_gameEndHandle);
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
			if (Input::GetInstance().IsTrigger(INPUT_X, num) && !_endFrag) {

				_frame = 0;

				// �t�F�[�h�A�E�g
				_updateFunc = &SceneTitle::NormalFadeOutUpdate;
				_drawFunc = &SceneTitle::NormalFadeDraw;
			}
			else if (Input::GetInstance().IsTrigger(INPUT_A, num) && !_endFrag) {

				// ���艹��炷
				SoundManager::GetInstance().RingSE(SE_TITLE_START);

				// �l���I���ֈڍs
				_updateFunc = &SceneTitle::SlideOutUpdate;
				_drawFunc = &SceneTitle::SlideOutDraw;
			}
			else if (Input::GetInstance().IsTrigger(INPUT_A, num) && _endFrag) {
				SceneManager::GetInstance().GameEnd();
			}
			else if (Input::GetInstance().IsTrigger(INPUT_B, num) && _endFrag) {
				_endFrag = false;
			}

			// start�{�^���������ꂽ��Q�[���I���m�F�摜��\��
			if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
				if (_endFrag) {
					_endFrag = false;
				}
				else {
					_endFrag = true;
				}
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
		DrawGraph(GetConstantInt("MASSAGE_POS_X"), GetConstantInt("MASSAGE_POS_Y"), _serihu, true);
	}
	else {
		DrawGraph(GetConstantInt("MASSAGE_POS_X"), GetConstantInt("MASSAGE_POS_Y"), _serihu2, true);
	}

	// �����̕`��
	_pModel1->Draw();
	_pModel2->Draw();

	// �Q�[���I���K�C�h�摜��\��
	DrawGraph(GetConstantInt("GAME_END_POS_X"), GetConstantInt("GAME_END_POS_Y"), _gameEndHandle, true);

	auto& app = Application::GetInstance();
	// �Q�[���I���摜�̕`��
	if (_endFrag) DrawRotaGraph(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, 1.0, 0.0, _endHandle, false);
}

void SceneTitle::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �X���C�h�摜�̈ړ�
	_slidePos.x += GetConstantInt("SLIDE_MOVE_SCALE");

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	// �ړ����I�������ʏ�̏�ԂɑJ��
	if (_slidePos.x > GetConstantInt("SLIDE_IN_START_X")) {
		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::SlideOutUpdate()
{
	// �X���C�h�摜�̈ړ� 
	_slidePos.x -= GetConstantInt("SLIDE_MOVE_SCALE");

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	_pText->Update();

	// �����̍X�V����
	_pModel1->Update();
	_pModel2->Update();

	// �ړ����I�������V�[���J��
	if (_slidePos.x <= GetConstantInt("SLIDE_OUT_START_X")) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelectMode>(false));
	}
}

void SceneTitle::SlideInDraw() const
{
	// �ʏ�̕`����s��
	NormalDraw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneTitle::SlideOutDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// �l���I���̕`��
	NormalDraw();

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

	_frame--;
	if (_frame == 0) {
		_updateFunc = &SceneTitle::NormalUpdate;
		_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeInDraw() const
{
	NormalDraw();
	auto& app = Application::GetInstance();
	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM") * 2));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, app.GetConstantInt("SCREEN_WIDTH"), app.GetConstantInt("SCREEN_HEIGHT"), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

	_frame--;
	if (_frame == 0) {

		_updateFunc = &SceneTitle::NormalUpdate;
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

	_frame++;
	if (_frame == Application::GetInstance().GetConstantInt("FRAME_NUM")) {

		// �V�[���̐؂�ւ�
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneCredit>());
	}
}

void SceneTitle::NormalFadeDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM")));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
#include "SceneSelectMode.h"
#include "SelectModeUi.h"
#include "DxLib.h"
#include "SkyDome.h"
#include "Input.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SceneMenu.h"
#include "SceneSelect.h"
#include "SceneTutorial.h"

SceneSelectMode::SceneSelectMode(bool slideInFlag):
	_titleFrag(false),
	_returnSelectFrag(slideInFlag)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelectMode::SlideInUpdate;
	_drawFunc = &SceneSelectMode::SlideInDraw;

	// UI�C���X�^���X�쐬
	_pUi = std::make_shared<SelectModeUi>();

	// �X�J�C�h�[���C���X�^���X�쐬
	_pSkyDome = std::make_shared<SkyDome>();

	// �X���C�h�摜�̃��[�h
	_slideHandle = LoadGraph("data/image/Slide.png");

	// �Z���N�g�V�[������߂��Ă�����X���C�h�摜�͍�����J��
	if (_returnSelectFrag) {
		_slidePos.x = -300;
	}
	else {
		_slidePos.x = -300;
	}

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);
}

SceneSelectMode::~SceneSelectMode()
{
}

void SceneSelectMode::Update()
{
	(this->*_updateFunc)();
}

void SceneSelectMode::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelectMode::NormalUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// UI�̍X�V����
	_pUi->Update();

	// B�{�^���Ń^�C�g���ɖ߂�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {

		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// �^�C�g���ɖ߂�t���O�𗧂Ă�
		_titleFrag = true;

		// �X���C�h�摜�̏����ʒu��ݒ肷��
		_slidePos.x = -3840;

		_updateFunc = &SceneSelectMode::SlideOutUpdate;
		_drawFunc = &SceneSelectMode::SlideOutDraw;
	}

	// A�{�^���őI�����Ă���{�^���̏���������
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		switch (_pUi->GetSelect())
		{
		case SOLO_MODE:
		case MULTI_MODE:
		case TUTORIAL_MODE:

			// �X���C�h�摜�̏����ʒu��ݒ肷��
			_slidePos.x = 2000;

			// �X���C�h�A�E�g�����Ɉڍs����
			_updateFunc = &SceneSelectMode::SlideOutUpdate;
			_drawFunc = &SceneSelectMode::SlideOutDraw;
			break;
		case OPTION_MODE:
			// ���j���[�V�[����ǉ�����
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(INPUT_PAD_1));
			break;
		default:
			break;
		}
	}
}

void SceneSelectMode::NormalDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();
}

void SceneSelectMode::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// UI�̍X�V����
	_pUi->Update();

	// �X���C�h�摜�̈ړ�

	if (_returnSelectFrag) {

		// �X���C�h�摜�̈ړ�
		_slidePos.x += 80;

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x >= 2000) {
			_updateFunc = &SceneSelectMode::NormalUpdate;
			_drawFunc = &SceneSelectMode::NormalDraw;
		}
	}
	else {

		// �X���C�h�摜�̈ړ�
		_slidePos.x -= 80;

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x <= -3840) {
			_updateFunc = &SceneSelectMode::NormalUpdate;
			_drawFunc = &SceneSelectMode::NormalDraw;
		}
	}

}

void SceneSelectMode::SlideOutUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();
	
	// UI�̍X�V����
	//_pUi->Update();

	// �^�C�g���t���O�ŏ�����ς���
	if (_titleFrag) {
		// �X���C�h�摜�̈ړ� 
		_slidePos.x += 80;

		// �ړ����I�������V�[���J��
		if (_slidePos.x >= -300) {
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(true));
		}
	}
	else {
		// �X���C�h�摜�̈ړ� 
		_slidePos.x -= 80;

		// �ړ����I�������V�[���J��
		if (_slidePos.x <= -300) {
			switch (_pUi->GetSelect())
			{
			case SOLO_MODE:
				SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(0));
				break;
			case MULTI_MODE:

				break;
			case TUTORIAL_MODE:
				SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTutorial>());
				break;
			case OPTION_MODE:
			default:
				break;
			}
		}
	}
}

void SceneSelectMode::SlideInDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectMode::SlideOutDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

#include "SceneSelectNum.h"
#include "SelectModeUi.h"
#include "SkyDome.h"
#include "SoundManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneSelectMode.h"
#include "PlayerManager.h"
#include "SceneSelect.h"
#include "Application.h"

SceneSelectNum::SceneSelectNum() :
	_selectFrag(false),
	_warningFrag(false),
	_returnFrag(false)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/SceneSelectNum.csv");

	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelectNum::SlideInUpdate;
	_drawFunc = &SceneSelectNum::SlideInDraw;

	// Ui�C���X�^���X�쐬
	_pUi = std::make_shared<SelectModeUi>(false);

	// �X�J�C�h�[���C���X�^���X�쐬
	_pSkyDome = std::make_shared<SkyDome>();

	// �X���C�h�摜�̃��[�h
	_slideHandle = LoadGraph("data/image/Slide.png");

	_slidePos.x = GetConstantInt("SLIDE_OUT_START_X");

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ GetConstantFloat("CAMERA_POS_X"),GetConstantFloat("CAMERA_POS_Y"),GetConstantFloat("CAMERA_POS_Z") },
		VECTOR{ GetConstantFloat("CAMERA_TARGET_X"), GetConstantFloat("CAMERA_TARGET_Y"), GetConstantFloat("CAMERA_TARGET_Z") });

	SetCameraNearFar(GetConstantFloat("CAMERA_NEAR"), GetConstantFloat("CAMERA_FAR"));

	// warning�摜�̃��[�h
	_warningHandle = LoadGraph("data/image/warning.png");

	// BGM�̍Đ�
	SoundManager::GetInstance().StartBGM(BGM_OPENING);
}

SceneSelectNum::~SceneSelectNum()
{
	DeleteGraph(_slideHandle);
	DeleteGraph(_warningHandle);
}

void SceneSelectNum::Update()
{
	(this->*_updateFunc)();
}

void SceneSelectNum::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelectNum::NormalUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// UI�̍X�V����
	if (!_warningFrag) {
		_pUi->Update();

	}

	// B�{�^���Ń��[�h�Z���N�g�ɖ߂�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {

		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// �^�C�g���ɖ߂�t���O�𗧂Ă�
		_selectFrag = true;

		// �X���C�h�摜�̏����ʒu��ݒ肷��
		_slidePos.x = GetConstantInt("SLIDE_OUT_END_X");

		_updateFunc = &SceneSelectNum::SlideOutUpdate;
		_drawFunc = &SceneSelectNum::SlideOutDraw;
	}

	// A�{�^���őI�����Ă���{�^���̏���������
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		if (_warningFrag) {
			_warningFrag = false;
			SoundManager::GetInstance().RingSE(SE_CLOSE_MENU);
		}
		else if (_pUi->GetSelect() + 1 > Input::GetInstance().GetPadNum()) {
			_warningFrag = true;
			SoundManager::GetInstance().RingSE(SE_BEEP);
		}
		else {


			// ���艹��炷
			SoundManager::GetInstance().RingSE(SE_CHARA_SELECT);

			// �X���C�h�摜�̏����ʒu��ݒ肷��
			_slidePos.x = GetConstantInt("SLIDE_IN_START_X");

			// �X���C�h�A�E�g�����Ɉڍs����
			_updateFunc = &SceneSelectNum::SlideOutUpdate;
			_drawFunc = &SceneSelectNum::SlideOutDraw;
		}
	}
}

void SceneSelectNum::NormalDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();

	// waring�\��
	if (_warningFrag) {
		DrawRotaGraph(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2, Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2, 1.0, 0.0, _warningHandle, true);
	}
}

void SceneSelectNum::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// UI�̍X�V����
	_pUi->Update();

	// �X���C�h�摜�̈ړ�

	if (_selectFrag) {

		// �X���C�h�摜�̈ړ�
		_slidePos.x += GetConstantInt("SLIDE_MOVE_SCALE");

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x >= GetConstantInt("SLIDE_IN_START_X")) {
			_updateFunc = &SceneSelectNum::NormalUpdate;
			_drawFunc = &SceneSelectNum::NormalDraw;
		}
	}
	else {

		// �X���C�h�摜�̈ړ�
		_slidePos.x -= GetConstantInt("SLIDE_MOVE_SCALE");

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x <= GetConstantInt("SLIDE_OUT_END_X")) {
			_updateFunc = &SceneSelectNum::NormalUpdate;
			_drawFunc = &SceneSelectNum::NormalDraw;
		}
	}

}

void SceneSelectNum::SlideOutUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// UI�̍X�V����
	//_pUi->Update();

	// �^�C�g���t���O�ŏ�����ς���
	if (_selectFrag) {
		// �X���C�h�摜�̈ړ� 
		_slidePos.x += GetConstantInt("SLIDE_MOVE_SCALE");

		// �ړ����I�������V�[���J��
		if (_slidePos.x >= GetConstantInt("SLIDE_OUT_START_X")) {

			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelectMode>(true));

		}
	}
	else {
		// �X���C�h�摜�̈ړ� 
		_slidePos.x -= GetConstantInt("SLIDE_MOVE_SCALE");

		// �ړ����I�������V�[���J��
		if (_slidePos.x <= GetConstantInt("SLIDE_OUT_START_X")) {

			// �v���C���[�f�[�^
			PlayerData data;

			data.aiFlag = false;
			data.playerNum = _pUi->GetSelect();

			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelect>(_pUi->GetSelect()));
		}
	}
}

void SceneSelectNum::SlideInDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectNum::SlideOutDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

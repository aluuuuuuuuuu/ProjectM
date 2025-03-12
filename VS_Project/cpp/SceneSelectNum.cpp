#include "SceneSelectNum.h"
#include "SelectModeUi.h"
#include "SkyDome.h"
#include "SoundManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneSelectMode.h"
#include "PlayerManager.h"
#include "SceneSelect.h"
#include "SoundManager.h"

SceneSelectNum::SceneSelectNum()
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelectNum::SlideInUpdate;
	_drawFunc = &SceneSelectNum::SlideInDraw;

	// Ui�C���X�^���X�쐬
	_pUi = std::make_shared<SelectModeUi>(false);

	// �X�J�C�h�[���C���X�^���X�쐬
	_pSkyDome = std::make_shared<SkyDome>();

	// �X���C�h�摜�̃��[�h
	_slideHandle = LoadGraph("data/image/Slide.png");

	// �Z���N�g�V�[������߂��Ă�����X���C�h�摜�͍�����J��
	if (_returnFrag) {
		_slidePos.x = -300;
	}
	else {
		_slidePos.x = -300;
	}

	// �J�����̏�����
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 100.0f, 250.0f, 0.0f }, VECTOR{ 150.0f, 250.0f, 0.0f });
	SetCameraNearFar(1, 1000);

	// BGM�̍Đ�
	SoundManager::GetInstance().StartBGM(BGM_OPENING);
}

SceneSelectNum::~SceneSelectNum()
{
	DeleteGraph(_slideHandle);
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
	_pUi->Update();

	// B�{�^���Ń��[�h�Z���N�g�ɖ߂�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {

		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// �^�C�g���ɖ߂�t���O�𗧂Ă�
		_selectFrag = true;

		// �X���C�h�摜�̏����ʒu��ݒ肷��
		_slidePos.x = -3840;

		_updateFunc = &SceneSelectNum::SlideOutUpdate;
		_drawFunc = &SceneSelectNum::SlideOutDraw;
	}

	// A�{�^���őI�����Ă���{�^���̏���������
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// ���艹��炷
		SoundManager::GetInstance().RingSE(SE_CHARA_SELECT);

		// �X���C�h�摜�̏����ʒu��ݒ肷��
		_slidePos.x = 2000;

		// �X���C�h�A�E�g�����Ɉڍs����
		_updateFunc = &SceneSelectNum::SlideOutUpdate;
		_drawFunc = &SceneSelectNum::SlideOutDraw;
	}


}

void SceneSelectNum::NormalDraw() const
{
	// �X�J�C�h�[���̕`�揈��
	_pSkyDome->Draw();

	// UI�̕`�揈��
	_pUi->Draw();
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
		_slidePos.x += 80;

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x >= 2000) {
			_updateFunc = &SceneSelectNum::NormalUpdate;
			_drawFunc = &SceneSelectNum::NormalDraw;
		}
	}
	else {

		// �X���C�h�摜�̈ړ�
		_slidePos.x -= 80;

		// �ړ����I������珈���̐؂�ւ�
		if (_slidePos.x <= -3840) {
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
		_slidePos.x += 80;

		// �ړ����I�������V�[���J��
		if (_slidePos.x >= -300) {

			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneSelectMode>(true));
			
		}
	}
	else {
		// �X���C�h�摜�̈ړ� 
		_slidePos.x -= 80;

		// �ړ����I�������V�[���J��
		if (_slidePos.x <= -300) {

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

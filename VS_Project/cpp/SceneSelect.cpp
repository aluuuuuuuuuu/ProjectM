#include "SceneSelect.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharacterCard.h"
#include "CharacterSelectManager.h"
#include "SelectUI.h"
#include "SceneTitle.h"
#include "SoundManager.h"
#include "SkyDome.h"
#include "ScenePause.h"

SceneSelect::SceneSelect(int num) :
	_frame(0)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelect::SlideInUpdate;
	_drawFunc = &SceneSelect::SlideInDraw;

	// �v���C���[�f�[�^�̏�����
	for (auto& pl : _plData.character) {
		pl = -1;
	}
	_plData.playerNum = num;

	// �C���X�^���X�̍쐬
	{
		_pSelectManager = std::make_shared<CharacterSelectManager>(_plData);	// �Z���N�g�}�l�[�W���[
		_pUi = std::make_shared<SelectUI>();	// ui
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
	}

	// �X���C�h�摜�̃��[�h
	_slideHandle = LoadGraph("data/image/Slide.png");

	_slidePos = Vec2{ -300,0 };
}

SceneSelect::~SceneSelect()
{
	DeleteGraph(_slideHandle);
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::CharacterSelectUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �Z���N�g�}�l�[�W���[�̍X�V
	_pSelectManager->Update();

	// �X�^�[�g�{�^���������ꂽ��Q�[���V�[���Ɉڍs����
	if (_pSelectManager->GetStart()) {

		// �v���C���[�f�[�^���쐬����
		_pSelectManager->CreateData();

		// �t�F�[�h�A�E�g�Ɉڍs
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}

	// �}�l�[�W���[�̖߂�t���O�������Ă�����l���I���ɖ߂�
	if (_pSelectManager->GetReturnFlag()) {

		// �L�����Z������炷
		SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);

		// �t�F�[�h�A�E�g�Ɉڍs
		_updateFunc = &SceneSelect::SlideOutUpdate;
		_drawFunc = &SceneSelect::SlideOutDraw;
	}
}

void SceneSelect::CharacterSelectDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// ui�̕`��
	_pUi->Draw();

	// �Z���N�g�}�l�[�W���[�̕`�揈��
	_pSelectManager->Draw();
}

void SceneSelect::SlideInUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �X���C�h�摜�̈ړ�
	_slidePos.x -= 80;
	if (_slidePos.x <= -3840) {
		_updateFunc = &SceneSelect::CharacterSelectUpdate;
		_drawFunc = &SceneSelect::CharacterSelectDraw;
	}
}

void SceneSelect::SlideInDraw() const
{
	// �ʏ�̕`����s��
	CharacterSelectDraw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelect::SlideOutUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	_slidePos.x += 80;
	if (_slidePos.x >= -300) {
		// ���̃V�[���Ɉڍs����
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(true));
	}
}

void SceneSelect::SlideOutDraw() const
{
	// �ʏ�̕`����s��
	CharacterSelectDraw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelect::FadeOutUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	_frame++;
	if (_frame > 60) {

		// ���̃V�[���Ɉڍs����
		SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePause>(_plData));
	}
}

void SceneSelect::FadeOutDraw() const
{
	// �ʏ�̕`����s��
	CharacterSelectDraw();

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

#include "SceneSelectMode.h"
#include "SelectModeUi.h"
#include "DxLib.h"
#include "SkyDome.h"

SceneSelectMode::SceneSelectMode(bool slideInFlag)
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

	// �X���C�h�摜�̏����ʒu
	_slidePos = Vec2{ -300,0 };

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
	_pSkyDome->Update();
	_pUi->Update();
}

void SceneSelectMode::NormalDraw() const
{
	_pSkyDome->Draw();

	_pUi->Draw();
}

void SceneSelectMode::SlideInUpdate()
{
	_pSkyDome->Update();
	// UI�̍X�V����
	_pUi->Update();

	// �X���C�h�摜�̈ړ�
	_slidePos.x -= 80;
}

void SceneSelectMode::SlideOutUpdate()
{
	_pSkyDome->Update();
	// UI�̍X�V����
	_pUi->Update();

	// �X���C�h�摜�̈ړ� 
	_slidePos.x += 80;
}

void SceneSelectMode::SlideInDraw() const
{
	_pSkyDome->Draw();
	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

void SceneSelectMode::SlideOutDraw() const
{
	_pSkyDome->Draw();

	

	// UI�̕`�揈��
	_pUi->Draw();

	// �X���C�h�摜�̕`��
	DrawGraph(_slidePos.intX(), _slidePos.intY(), _slideHandle, true);
}

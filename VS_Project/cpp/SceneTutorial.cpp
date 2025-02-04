#include "SceneTutorial.h"
#include "TutorialManager.h"
#include "SceneManager.h"
#include "SceneTitle.h"

SceneTutorial::SceneTutorial():
	_frame(60)
{
	// �}�l�[�W���[�̃C���X�^���X�쐬
	_pManager = std::make_shared<TutorialManager>();

	// �֐��|�C���^�̏�����
	_updateFunc = &SceneTutorial::FadeInUpdate;
	_drawFunc = &SceneTutorial::FadeInDraw;
}

SceneTutorial::~SceneTutorial()
{
	// ���C�g�̍폜
	DeleteLightHandleAll();
}

void SceneTutorial::Update()
{
	(this->*_updateFunc)();
}

void SceneTutorial::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTutorial::NormalUpdate()
{
	_pManager->Update();
}

void SceneTutorial::NormalDraw() const
{
	_pManager->Draw();
}

void SceneTutorial::FadeInUpdate()
{
	_frame--;
	if (_frame == 0) {
		_updateFunc = &SceneTutorial::NormalUpdate;
		_drawFunc = &SceneTutorial::NormalDraw;
	}
}

void SceneTutorial::FadeOutUpdate()
{
	_frame++;
	if (_frame > 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(false));
	}
}

void SceneTutorial::FadeInDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTutorial::FadeOutDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

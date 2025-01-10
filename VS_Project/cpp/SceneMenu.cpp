#include "SceneMenu.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "MenuManager.h"
#include "Application.h"

SceneMenu::SceneMenu(int padNum) :
	_padNum(padNum),
	_flame(0)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneMenu::StartUpdate;
	_drawFunc = &SceneMenu::StartDraw;

	// ���j���[�}�l�[�W���[�̃|�C���^���쐬
	_manager = std::make_shared<MenuManager>(_padNum);

	// �`��͈͂ƕ`���̒��S�̏�����
	SetDrawArea(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"));
	SetCameraScreenCenter(static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2), static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2));
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Update()
{
	(this->*_updateFunc)();
}

void SceneMenu::Draw() const
{
	(this->*_drawFunc)();
}

void SceneMenu::StartUpdate()
{
	// �}�l�[�W���[�̍X�V����
	_manager->Update();
}

void SceneMenu::StartDraw() const
{
	// ���j���[�}�l�[�W���[�̕`�揈��
	_manager->Draw();
}


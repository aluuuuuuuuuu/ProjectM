#include "SceneMenu.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "MenuManager.h"

SceneMenu::SceneMenu(int padNum):
	_padNum(padNum),
	_flame(0)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneMenu::FadeInUpdate;
	_drawFunc = &SceneMenu::FadeDraw;

	// ���j���[�}�l�[�W���[�̃|�C���^���쐬
	_pManager = std::make_shared<MenuManager>(_padNum);

	// �w�i�ڂ����摜
	_backHandle = LoadGraph("data/image/backBloom.png");
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

void SceneMenu::NormalUpdate()
{
	// �X�^�[�g�{�^���������ƃt�F�[�h�A�E�g����
	if (Input::GetInstance().IsTrigger(INPUT_START, _padNum)) {
		_updateFunc = &SceneMenu::FadeOutUpdate;
		_drawFunc = &SceneMenu::FadeDraw;
	}

	// �}�l�[�W���[�̍X�V����
	_pManager->Update();
}

void SceneMenu::NormalDraw() const
{
	// �ڂ����̕`��
	DrawGraph(1, 0, _backHandle, true);

	// ���j���[�}�l�[�W���[�̕`�揈��
	_pManager->Draw();
}

void SceneMenu::FadeInUpdate()
{
	// �}�l�[�W���[�̍X�V����
	_pManager->Update();

	_flame++;
	if (_flame >= 5) {
		_updateFunc = &SceneMenu::NormalUpdate;
		_drawFunc = &SceneMenu::NormalDraw;
	}
}

void SceneMenu::FadeOutUpdate()
{
	// �}�l�[�W���[�̍X�V����
	_pManager->Update();

	_flame--;
	if (_flame <= 0) {
		SceneManager::GetInstance().PopScene();
	}
}

void SceneMenu::FadeDraw() const
{
	// �ڂ����̕`��
	DrawGraph(0, 0, _backHandle, true);

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 5));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// ���j���[�}�l�[�W���[�̕`�揈��
	_pManager->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

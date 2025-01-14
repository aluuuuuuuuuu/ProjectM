#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "CharactorSelectManager.h"
#include "SelectUI.h"
#include "SceneTitle.h"

SceneSelect::SceneSelect(int num) :
	_flame(60),
	_nextScene(0)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeInDraw;

	// �v���C���[�f�[�^�̏�����
	for (auto& pl : _plData.charactor) {
		pl = -1;
	}
	_plData.playerNum = num;

	// �Z���N�g�}�l�[�W���[�̍쐬
	_pSelectManager = std::make_shared<CharactorSelectManager>(_plData);

	// ui�C���X�^���X�̍쐬
	_pUi = std::make_shared<SelectUI>();

	// �w�i�摜�̃��[�h
	back = LoadGraph("data/image/back.jpg");
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Update()
{
	(this->*_updateFunc)();
}

void SceneSelect::Draw() const
{
	(this->*_drawFunc)();
}

void SceneSelect::CharactorSelectUpdate()
{
	// �Z���N�g�}�l�[�W���[�̍X�V
	_pSelectManager->Update();

	// �X�^�[�g�{�^���������ꂽ��Q�[���V�[���Ɉڍs����
	if (_pSelectManager->GetStart()) {

		// �v���C���[�f�[�^���쐬����
		_pSelectManager->CreateData();

		// ���̃V�[�����Z���N�g�V�[���ɐ؂�ւ���
		_nextScene = SCENE_TEST;

		// �t�F�[�h�A�E�g�Ɉڍs
		_updateFunc = &SceneSelect::FadeOutUpdate;
		_drawFunc = &SceneSelect::FadeOutDraw;
	}

	// B�{�^���������ꂽ��l���I���ɖ߂�
	for (int i = 0; i < Input::GetInstance().GetPadNum(); i++) {
		if (Input::GetInstance().IsTrigger(INPUT_B, i)) {

			// ���̃V�[�����^�C�g���V�[���ɐ؂�ւ���
			_nextScene = SCENE_TITLE;

			// �t�F�[�h�A�E�g�Ɉڍs
			_updateFunc = &SceneSelect::FadeOutUpdate;
			_drawFunc = &SceneSelect::FadeOutDraw;
		}
	}
}

void SceneSelect::CharactorSelectDraw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, back, true);

	// ui�̕`��
	_pUi->Draw();

	// �Z���N�g�}�l�[�W���[�̕`�揈��
	_pSelectManager->Draw();
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {

		// ���̃V�[���Ɉڍs����
		switch (_nextScene)
		{
		case SCENE_TITLE:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
			break;
		case SCENE_TEST:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_plData));
			break;
		default:
			break;
		}
	}
}

void SceneSelect::FadeInDraw() const
{
	CharactorSelectDraw();

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::FadeOutDraw() const
{
	CharactorSelectDraw();

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

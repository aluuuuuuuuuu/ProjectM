#include "SceneSelect.h"
#include "SceneTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "CharactorSelectManager.h"

SceneSelect::SceneSelect():
	_flame(60)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneSelect::FadeInUpdate;
	_drawFunc = &SceneSelect::FadeInDraw;

	// �v���C���[�f�[�^�̏�����
	for (auto& pl : _plData.player) {
		pl = -1;
	}

	// �ŏ��̐l���͂��Ȃ炸��l
	_plData.playerNum = 1;


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

void SceneSelect::PlayerNumSelectUpdate()
{
	// B�{�^���Ől���̐؂�ւ�
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		if (_plData.playerNum == Input::GetInstance().GetPadNum()) {
			_plData.playerNum = 1;
		}
		else {
			_plData.playerNum++;
		}
	}

	// A�{�^���Ŏ��̉�ʂ�
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {

		// �Z���N�g�}�l�[�W���[�̍쐬
		_pSelectManager = std::make_shared<CharactorSelectManager>(_plData);

		// �L�����N�^�[�I���Ɉڍs
		_updateFunc = &SceneSelect::CharactorSelectUpdate;
		_drawFunc = &SceneSelect::CharactorSelectDraw;
	}
}

void SceneSelect::PlayerNumSelectDraw() const
{
	switch (_plData.playerNum)
	{
	case 1:
		DrawFormatString(10, 10, 0xffffff, "1�l");
		break;
	case 2:
		DrawFormatString(10, 30, 0xffffff, "2�l");
		break;
	case 3:
		DrawFormatString(10, 50, 0xffffff, "3�l");
		break;
	case 4:
		DrawFormatString(10, 70, 0xffffff, "4�l");
		break;
	default:
		break;
	}

	DrawCircle(800, 400, 200, 0x000000);
}

void SceneSelect::CharactorSelectUpdate()
{
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
}

void SceneSelect::CharactorSelectDraw() const
{
	// �w�i�摜�̕`��
	DrawGraph(0, 0, back,true);

	// �Z���N�g�}�l�[�W���[�̕`�揈��
	_pSelectManager->Draw();
}

void SceneSelect::FadeInUpdate()
{
	_flame--;
	if (_flame <= 0) {
		_updateFunc = &SceneSelect::PlayerNumSelectUpdate;
		_drawFunc = &SceneSelect::PlayerNumSelectDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	_flame++;
	if (_flame >= 60) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_plData));
	}
}

void SceneSelect::FadeInDraw() const
{
	PlayerNumSelectDraw();

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

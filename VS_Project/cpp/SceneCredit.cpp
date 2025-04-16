#include "SceneCredit.h"
#include "DxLib.h"
#include "CreditCharacter.h"
#include "SoundManager.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"
#include "Application.h"

SceneCredit::SceneCredit() :
	_frame(Application::GetInstance().GetConstantInt("FRAME_NUM")),
	_creditY(0),
	_creditFrame(0)
{
	// �֐��|�C���^�̏�����
	_updateFunc = &SceneCredit::FadeInUpdate;
	_drawFunc = &SceneCredit::FadeDraw;

	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/SceneCredit.csv");

	// ���f���̃C���X�^���X�̍쐬
	_pChar1 = std::make_shared<CreditCharacter>(0);
	_pChar2 = std::make_shared<CreditCharacter>(1);
	_pChar3 = std::make_shared<CreditCharacter>(2);
	_pChar4 = std::make_shared<CreditCharacter>(3);

	// �N���W�b�g�摜�̃��[�h
	_creditHandle = LoadGraph("data/image/Credit.png");

	// BGM�̕ύX
	SoundManager::GetInstance().StopBGM(BGM_OPENING);
	SoundManager::GetInstance().StartBGM(BGM_THEME);
}

SceneCredit::~SceneCredit()
{
	DeleteGraph(_creditHandle);
}

void SceneCredit::Update()
{
	(this->*_updateFunc)();
}

void SceneCredit::Draw() const
{
	(this->*_drawFunc)();
}

void SceneCredit::NormalUpdate()
{
	// B�{�^���������ꂽ��^�C�g���V�[���ɐ؂�ւ�
	for (int num = 0; num < Input::GetInstance().GetPadNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {

			// �t�F�[�h�A�E�g�Ɉڍs
			_updateFunc = &SceneCredit::FadeOutUpdate;
			_drawFunc = &SceneCredit::FadeDraw;
		}
	}

	// �t���[���̉��Z
	_creditFrame++;

	if (_creditFrame > GetConstantInt("DOWN_START_FRAME")) {
		if (_creditY > -GetConstantInt("IMAGE_HEIGHT") + Application::GetInstance().GetConstantInt("SCREEN_HEIGHT")) {
			// �N���W�b�g���W�̈ړ�
			_creditY--;
		}
	}

	// BGM���I�������ʏ�̏����ɖ߂�
	if (_creditFrame == GetConstantInt("SOUND_END_FRAME")) {
		// BGM��ς���
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		// �t�F�[�h�A�E�g�Ɉڍs
		_updateFunc = &SceneCredit::FadeOutUpdate;
		_drawFunc = &SceneCredit::FadeDraw;
	}

	if (_creditFrame == GetConstantInt("ALL_IN_FRAME")) {
		_pChar1->PosSet();
		_pChar2->PosSet();
		_pChar3->PosSet();
		_pChar4->PosSet();
	}

	// ���f���̍X�V
	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();
}

void SceneCredit::NormalDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);

	if (_creditFrame < GetConstantInt("POP_CHARACOTR_ONE_FRAME")) {
		_pChar1->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_TWO_FRAME")) {
		_pChar2->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_THREE_FRAME")) {
		_pChar3->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_FOUR_FRAME")) {
		_pChar4->Draw();
	}
	else {
		_pChar1->Draw();
		_pChar2->Draw();
		_pChar3->Draw();
		_pChar4->Draw();
	}
}

void SceneCredit::FadeInUpdate()
{
	// �t���[���̉��Z
	_frame--;

	// �L�����N�^�[�̍X�V����
	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();

	// �ʏ�̏����Ɉڍs����
	if (_frame == 0) {

		_updateFunc = &SceneCredit::NormalUpdate;
		_drawFunc = &SceneCredit::NormalDraw;
	}
}

void SceneCredit::FadeOutUpdate()
{
	// �t���[���̉��Z
	_creditFrame++;

	// �L�����N�^�[�̍X�V����
	_pChar1->Update();
	_pChar2->Update();
	_pChar3->Update();
	_pChar4->Update();

	if (_creditFrame > GetConstantInt("DOWN_START_FRAME")) {
		if (_creditY > -GetConstantInt("IMAGE_HEIGHT") + Application::GetInstance().GetConstantInt("SCREEN_HEIGHT")) {
			// �N���W�b�g���W�̈ړ�
			_creditY--;
		}
	}

	_frame++;
	if (_frame == Application::GetInstance().GetConstantInt("FRAME_NUM")) {
		SoundManager::GetInstance().StopBGM(BGM_THEME);
		SoundManager::GetInstance().StartBGM(BGM_OPENING);

		// �^�C�g���V�[���ɐ؂�ւ�
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(false));
	}
}

void SceneCredit::FadeDraw() const
{
	DrawGraph(0, _creditY, _creditHandle, true);

	if (_creditFrame < GetConstantInt("POP_CHARACOTR_ONE_FRAME")) {
		_pChar1->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_TWO_FRAME")) {
		_pChar2->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_THREE_FRAME")) {
		_pChar3->Draw();
	}
	else if (_creditFrame < GetConstantInt("POP_CHARACOTR_FOUR_FRAME")) {
		_pChar4->Draw();
	}
	else {
		_pChar1->Draw();
		_pChar2->Draw();
		_pChar3->Draw();
		_pChar4->Draw();
	}

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM")));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

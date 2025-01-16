#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"
#include "ResultCharacter.h"
#include "SoundManager.h"

SceneResult::SceneResult(PlayerData data, int gameTime) :
	_playerData(data),
	_flame(0),
	_nextScene(0)
{
	// �L�����N�^�[�̍쐬
	_pCharacter = std::make_shared<ResultCharacter>(data.winner);

	// �����̍쐬
	_pNum = std::make_shared<NumUtility>(1.0f, Vec2{ 10,350 }, gameTime);

	// ���U���gUI�̍쐬
	_pResultUi = std::make_shared<ResultUi>(gameTime);

	// �֐��|�C���^�̏�����
	_updateFunc = &SceneResult::StartUpdate;
	_drawFunc = &SceneResult::StartDraw;

	// �V���O���̍Đ�
	SoundManager::GetInstance().RingSE(SE_RESULT);
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	(this->*_updateFunc)();
}

void SceneResult::Draw() const
{
	(this->*_drawFunc)();
}

void SceneResult::StartUpdate()
{

	for (int num = 0; num <= _playerData.playerNum; num++) {

		// A�{�^���������ꂽ�烊�X�^�[�g
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {
			_nextScene = SCENE_TEST;
			_updateFunc = &SceneResult::FadeOutUpdate;
			_drawFunc = &SceneResult::FadeOutDraw;
		}

		// B�{�^���������ꂽ��^�C�g�����
		if (Input::GetInstance().IsTrigger(INPUT_B, num)) {
			_nextScene = SCENE_TITLE;
			_updateFunc = &SceneResult::FadeOutUpdate;
			_drawFunc = &SceneResult::FadeOutDraw;
		}

		// START�{�^���������ꂽ�烁�j���[���J��
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}

	// �L�����N�^�[�̍X�V����
	_pCharacter->Update();
}

void SceneResult::StartDraw() const
{
	// �L�����N�^�[�̕`��
	_pCharacter->Draw();

	// ���U���gUI�̕`��
	_pResultUi->Draw();

	// �����̕`��
	_pNum->Draw();

#ifdef _DEBUG
	DrawString(10, 10, "A�{�^���Ń��X�^�[�g", 0xffffff);
	DrawString(10, 40, "B�{�^���Ń^�C�g����ʂ�", 0xffffff);
	DrawString(10, 70, "START�{�^���Ń��j���[", 0xffffff);
#endif // DEBUG
}

void SceneResult::FadeOutUpdate()
{
	_flame++;

	// �t�F�[�h���I��������
	if (_flame >= 110) {
		// ���̃V�[���ɐ؂�ւ���
		switch (_nextScene)
		{
		case SCENE_TEST:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerData));
			break;
		case SCENE_TITLE:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
			break;
		default:
			break;
		}
	}
}

void SceneResult::FadeOutDraw() const
{
	StartDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_flame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

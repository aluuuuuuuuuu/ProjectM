#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "ScenePvp.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"
#include "ResultCharacter.h"
#include "SoundManager.h"
#include "ScenePve.h"
#include "SkyDome.h"

SceneResult::SceneResult(PlayerData data, int gameTime) :
	_playerData(data),
	_frame(0),
	_nextScene(0)
{
	// �L�����N�^�[�̍쐬
	_pCharacter = std::make_shared<ResultCharacter>(data.winner);

	// �����̍쐬
	_pNum = std::make_shared<NumUtility>(1.0f, Vec2{ 10,400 }, gameTime);

	// �X�J�C�h�[���̍쐬
	_pSkyDome = std::make_shared<SkyDome>();

	// ���U���gUI�̍쐬
	_pResultUi = std::make_shared<ResultUi>(gameTime);

	// �֐��|�C���^�̏�����
	_updateFunc = &SceneResult::NormalUpdate;
	_drawFunc = &SceneResult::NormalDraw;

	// �L�����N�^�[�̍X�V����
	_pCharacter->Update();

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

void SceneResult::NormalUpdate()
{
	auto plNum = _playerData.playerNum;

	// AI�t���O�������Ă�����v���C���[�̐l������l���炷
	if (_playerData.aiFlag) {
		plNum--;
	}

	// �v���C���[�̐�����������s��
	for (int num = 0; num <= plNum; num++) {

		// A�{�^���������ꂽ�烊�X�^�[�g
		if (Input::GetInstance().IsTrigger(INPUT_A, num)) {

			// AI��ł����PVE�V�[���ɖ߂�
			if (_playerData.aiFlag) {
				_nextScene = SCENE_PVE;
			}
			else {
				_nextScene = SCENE_PVP;
			}

			// �t�F�[�h�A�E�g�Ɉڍs
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

	// �X�J�C�h�[���̍X�V
	_pSkyDome->Update();

	// �L�����N�^�[�̍X�V����
	_pCharacter->Update();
}

void SceneResult::NormalDraw() const
{
	// �X�J�C�h�[���̕`��
	_pSkyDome->Draw();
	
	// �L�����N�^�[�̕`��
	_pCharacter->Draw();

	// ���U���gUI�̕`��
	_pResultUi->Draw();

	// �����̕`��
	_pNum->Draw();
}

void SceneResult::FadeOutUpdate()
{
	_frame++;

	// �t�F�[�h���I��������
	if (_frame > 110) {
		// ���̃V�[���ɐ؂�ւ���
		switch (_nextScene)
		{
		case SCENE_PVP:
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePvp>(_playerData));
			break;
		case SCENE_PVE:
			_playerData.playerNum--;
			SceneManager::GetInstance().ChangeScene(std::make_shared<ScenePve>(_playerData));
			break;
		case SCENE_TITLE:
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(false));
			break;
		default:
			break;
		}
	}
}

void SceneResult::FadeOutDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / 110));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

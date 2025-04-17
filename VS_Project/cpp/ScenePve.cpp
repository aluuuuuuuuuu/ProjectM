#include "ScenePve.h"
#include "StageManager.h"
#include "Player.h"
#include "StageCollisionManager.h"
#include "BulletManager.h"
#include "Input.h"
#include "MapBulletCollisionManager.h"
#include "Application.h"
#include "Vec3.h"
#include "SkyDome.h"
#include "SceneMenu.h"
#include "SceneManager.h"
#include "WedgewormManager.h"
#include "GameFlowManager.h"
#include "SceneResult.h"
#include "NumUtility.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "PlayerBulletCollisionManager.h"
#include "ItemManager.h"

ScenePve::ScenePve(PlayerData data) :
	_frame(Application::GetInstance().GetConstantInt("FRAME_NUM") * 2)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/ScenePve.csv");

	// �^�C�g����BGM���~�߂�
	SoundManager::GetInstance().StopBGM(BGM_OPENING);

	// �e�N���X�̃C���X�^���X�쐬
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// �S���}�l�[�W���[
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);	// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// �v���C���[�}�l�[�W���[
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// �Q�[���t���[�}�l�[�W���[
		_pNum = std::make_shared<NumUtility>(GetConstantFloat("NUM_SIZE"), Vec2{ GetConstantFloat("NUM_POS_X"),GetConstantFloat("NUM_POS_Y") });	// �������[�e�B���e�B
		_pPlayerBulletCollisionManager = std::make_shared<PlayerBulletCollisionManager>(_pBulletManager, _pPlayerManager);
		_pItemManager = std::make_shared<ItemManager>(_pPlayerManager, _pStage);
	}

	// AI�̒ǉ�
	_pPlayerManager->AddAi();

	// ���C�g�̐ݒ�
	{
		auto& app = Application::GetInstance();
		// ���C�e�B���O���g�p����
		SetUseLighting(true);

		// ���C�g�̃J���[�𒲐�����
		SetLightDifColor(GetColorF(app.GetConstantFloat("LIGHT_COLOR_R"),
			app.GetConstantFloat("LIGHT_COLOR_G"),
			app.GetConstantFloat("LIGHT_COLOR_B"),
			app.GetConstantFloat("LIGHT_COLOR_ALPHA")));

		// ���C�g�̊p�x��ݒ�
		SetLightDirection(VECTOR{ app.GetConstantFloat("LIGHT_DIRECTION_X"),
			app.GetConstantFloat("LIGHT_DIRECTION_Y"),
			app.GetConstantFloat("LIGHT_DIRECTION_Z"), });
	}

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &ScenePve::FadeInUpdate;
		_drawFunc = &ScenePve::FadeInDraw;
	}

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();
}

ScenePve::~ScenePve()
{
	// ���C�g�̍폜
	DeleteLightHandleAll();

	// �`��͈͂ƕ`���̒��S�̏�����
	SetDrawArea(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"));
	SetCameraScreenCenter(static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2), static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2));
}

void ScenePve::Update()
{
	(this->*_updateFunc)();
}

void ScenePve::Draw() const
{
	(this->*_drawFunc)();
}

void ScenePve::NormalUpdate()
{
	// BGM���Đ�	
	SoundManager::GetInstance().StartBGM(BGM_BATTLE);

	// ���j���[��ʂ��J��
	if (Input::GetInstance().IsTrigger(INPUT_START, INPUT_PAD_1)) {
		SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(INPUT_PAD_1));
	}

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �A�C�e���̍X�V����
	_pItemManager->Update();

	// �Q�[���t���[�̍X�V����
	_pGameFlowManager->Update();

	// �o���b�g�̍X�V
	_pBulletManager->Update();

	// �S���̍X�V
	_pWedgewormManager->Update();

	// �v���C���[�R���W�����}�l�[�W���[�̍X�V
	_pPlayerBulletCollisionManager->Update();

	// �Q�[�����I�����Ă�����I�����̏����Ɉڂ�
	if (_pGameFlowManager->GetGameEnd()) {
		_updateFunc = &ScenePve::EndUpdate;
		_drawFunc = &ScenePve::EndDraw;
	}

	// ���Ԃ̍X�V����
	_pNum->Update(_pGameFlowManager->GetGameTime());
}

void ScenePve::NormalDraw() const
{
	// �J�����̐ݒ�
	_pPlayerManager->CameraSet(0);

	//�X�J�C�h�[���̕`��
	_pSkyDome->Draw();

	// �o���b�g�̕`��
	_pBulletManager->Draw();

	// �X�e�[�W�̕`��
	_pStage->DrawStage();

	// �S���̕`��
	_pWedgewormManager->Draw();

	// �A�C�e���̕`��
	_pItemManager->Draw();

	// �G�t�F�N�g�̕`��
	EffectManager::GetInstance().Draw();

	// �v���C���[�̕`��
	_pPlayerManager->Draw(0);

	// ���Ԃ̍X�V����
	_pNum->Draw();

}

void ScenePve::EndUpdate()
{
	// �Q�[���t���[�}�l�[�W���[�̍X�V
	_pGameFlowManager->Update();

	_pPlayerManager->Update();

	_frame++;

	// �Q�[�����I�����Ă���2�b���Ă΃��U���g��ʂֈڍs
	if (_frame >= Application::GetInstance().GetConstantInt("FRAME_NUM") * 2) {

		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	}
}

void ScenePve::EndDraw() const
{
	// �ʏ�̕`��
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM") * 2));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void ScenePve::FadeInUpdate()
{
	// �ʏ�̍X�V
	NormalUpdate();

	_frame--;
	if (_frame == 0) {
		_updateFunc = &ScenePve::NormalUpdate;
		_drawFunc = &ScenePve::NormalDraw;
	}
}

void ScenePve::FadeInDraw() const
{
	// �ʏ�̕`��
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM") * 2));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

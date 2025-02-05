#include "SceneTest.h"
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

SceneTest::SceneTest(PlayerData& data)
{
	// �^�C�g����BGM���~�߂�
	SoundManager::GetInstance().StopBGM(BGM_OPENING);

	// �e�N���X�̃C���X�^���X�쐬
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// �S���}�l�[�W���[
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager,_pWedgewormManager);				// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// �v���C���[�}�l�[�W���[
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// �Q�[���t���[�}�l�[�W���[
		_pNum = std::make_shared<NumUtility>(0.5f,Vec2{ 734,100 });	// �������[�e�B���e�B
	}

	// ���C�g�̐ݒ�
	{
		// ���C�e�B���O���g�p����
		SetUseLighting(true);

		// ���C�g�̃J���[�𒲐�����
		SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

		// ���C�g�̊p�x��ݒ�
		SetLightDirection(VECTOR{ 1.0f, -1.0f ,0.0f, });
	}

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}
}

SceneTest::~SceneTest()
{
	// ���C�g�̍폜
	DeleteLightHandleAll();

	// �`��͈͂ƕ`���̒��S�̏�����
	SetDrawArea(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"));
	SetCameraScreenCenter(static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2), static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2));
}

void SceneTest::Update()
{
	(this->*_updateFunc)();
}

void SceneTest::Draw() const
{
	(this->*_drawFunc)();
}

void SceneTest::NormalUpdate()
{
	SoundManager::GetInstance().StartBGM(BGM_BATTLE);

	// ���j���[��ʂ��J��
	for (int num = 0; num < _pPlayerManager->GetPlayerNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}

	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �Q�[���t���[�̍X�V����
	_pGameFlowManager->Update();

	// �o���b�g�̍X�V
	_pBulletManager->Update();

	// �S���̍X�V
	_pWedgewormManager->Update();

	// �Q�[�����I�����Ă�����I�����̏����Ɉڂ�
	if (_pGameFlowManager->GetGameEnd()) {
		_updateFunc = &SceneTest::EndUpdate;
		_drawFunc = &SceneTest::EndDraw;
	}

	// ���Ԃ̍X�V����
	_pNum->Update(_pGameFlowManager->GetGameTime());
}

void SceneTest::NormalDraw() const
{
	// �v���C���[�̉�ʂ̐������`�悷��
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// �J�����̐ݒ�
		_pPlayerManager->CameraSet(i);

		// �`��͈͂̐ݒ�
		SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

		// �`���̒��S��ݒ�
		SetCameraScreenCenter(static_cast<float>(_pPlayerManager->GetCenter(i).a), static_cast<float>(_pPlayerManager->GetCenter(i).b));

		//�X�J�C�h�[���̕`��
		_pSkyDome->Draw();

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�̕`��
		_pStage->DrawStage();

		// �S���̕`��
		_pWedgewormManager->Draw();

		// �v���C���[�̕`��
		_pPlayerManager->Draw(i);
	}

	// �`��͈͂̐ݒ�
	SetDrawArea(0, 0, 1920, 1080);

	// �`���̒��S��ݒ�
	SetCameraScreenCenter(static_cast<float>(1920 / 2), static_cast<float>(1080 / 2));

	// �����̕`��
	_pNum->Draw();

}

void SceneTest::EndUpdate()
{	
	// �Q�[���t���[�}�l�[�W���[�̍X�V
	_pGameFlowManager->Update();

	// �Q�[�����I�����Ă���P�Q�O�t���[�����Ă΃��U���g��ʂֈڍs
	if (_pGameFlowManager->GetFlameCount() >= 120) {
		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(),_pGameFlowManager->GetGameTime()));
	}
}

void SceneTest::EndDraw() const
{
	// �v���C���[�̉�ʂ̐������`�悷��
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// �J�����̐ݒ�
		_pPlayerManager->CameraSet(i);

		// �`��͈͂̐ݒ�
		SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

		// �`���̒��S��ݒ�
		SetCameraScreenCenter(static_cast<float>(_pPlayerManager->GetCenter(i).a), static_cast<float>(_pPlayerManager->GetCenter(i).b));

		//�X�J�C�h�[���̕`��
		_pSkyDome->Draw();

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�̕`��
		_pStage->DrawStage();

		// �S���̕`��
		_pWedgewormManager->Draw();

		// �v���C���[�̕`��
		_pPlayerManager->Draw(i);
	}
}

#include "SceneGrapple.h"
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

SceneGrapple::SceneGrapple()
{
	// �����V�[����ݒ�
	PlayerData data;

	data.playerNum = 1;
	data.charactor[0] = 1;

	// �C���X�^���X
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// �S���}�l�[�W���[
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);				// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// �v���C���[�}�l�[�W���[
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// �Q�[���t���[�}�l�[�W���[
	}
}

SceneGrapple::~SceneGrapple()
{
}

void SceneGrapple::Update()
{
	for (int num = 0; num < _pPlayerManager->GetPlayerNum(); num++) {
		if (Input::GetInstance().IsTrigger(INPUT_START, num)) {
			SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(num));
		}
	}


	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �o���b�g�̍X�V
	_pBulletManager->Update();

	// �S���̍X�V
	_pWedgewormManager->Update();

}

void SceneGrapple::Draw() const
{
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

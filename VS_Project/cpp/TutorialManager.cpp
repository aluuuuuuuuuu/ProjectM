#include "TutorialManager.h"
#include "BulletManager.h"
#include "StageManager.h"
#include "MapBulletCollisionManager.h"
#include "StageCollisionManager.h"
#include "PlayerManager.h"
#include "SkyDome.h"
#include "WedgewormManager.h"
#include "EffectManager.h"

TutorialManager::TutorialManager():
	_frame(60)
{
	PlayerData data;

	data.aiFlag = false;
	data.character[PLAYER_ONE] = 0;
	data.playerNum = PLAYER_ONE;

	// �e�N���X�̃C���X�^���X�쐬
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// �S���}�l�[�W��
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);	// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// �v���C���[�}�l�[�W���[
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
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
	_updateFunc = &TutorialManager::CameraUpdate;
	_drawFunc = &TutorialManager::ShareDraw;

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Update()
{
	(this->*_updateFunc)();
}

void TutorialManager::Draw() const
{
	(this->*_drawFunc)();
}

void TutorialManager::CameraUpdate()
{
	// �X�J�C�h�[���̍X�V����
	_pSkyDome->Update();

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �o���b�g�̍X�V
	_pBulletManager->Update();

	// �S���̍X�V
	_pWedgewormManager->Update();
}

void TutorialManager::MoveUpdate()
{
}

void TutorialManager::JumpUpdate()
{
}

void TutorialManager::ShotUpdate()
{
}

void TutorialManager::SelectUpdate()
{
}

void TutorialManager::LastUpdate()
{
}

void TutorialManager::ShareDraw() const
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

	// �G�t�F�N�g�̕`��
	EffectManager::GetInstance().Draw();

	// �v���C���[�̕`��
	_pPlayerManager->Draw(0);
}

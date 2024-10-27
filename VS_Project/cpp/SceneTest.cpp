#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
#include "PlayerManager.h"
#include "StageCollisionManager.h"
#include "BulletManager.h"
#include "Input.h"
#include "MapBulletCollisionManager.h"
#include "Application.h"

SceneTest::SceneTest(int playerNum)
{
	// �e�N���X�̃C���X�^���X�쐬
	{
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager);				// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStageCollisionManager, _pBulletManager, playerNum);	// �v���C���[�}�l�[�W���[
	}

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}
}

SceneTest::~SceneTest()
{
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
	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �o���b�g�̍X�V
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// �`��͈͂̐ݒ�
		SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

		// �`���̒��S��ݒ�
		SetCameraScreenCenter(_pPlayerManager->GetCenter(i).a, _pPlayerManager->GetCenter(i).b);

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�̕`��
		_pStage->DrawStage();

		// �v���C���[�̕`��
		_pPlayerManager->Draw(i);
	}
}

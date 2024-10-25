#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
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

		for (int a = 0; a < playerNum; a++) {
			_pPlayer.push_back(std::make_shared<Player>(_pStageCollisionManager, _pBulletCollsionManager, a));
		}
	}

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}

	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
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

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}

void SceneTest::NormalUpdate()
{
	// �v���C���[�̍X�V����
	for (auto& pl : _pPlayer) {
		pl->Update();
	}

	// �o���b�g�̍X�V
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	for (auto& pl : _pPlayer) {

		// �J�����̃Z�b�g
		pl->CameraSet();

		// �`��͈͂̐ݒ�
		VECTOR4 area = CreateDrawArea(_pPlayer.size());
		Vec2 center = CreateScreenCenter(_pPlayer.size());

		// �`��͈͂̐ݒ�
		SetDrawArea(area.a, area.b, area.c, area.d);

		// �`���̒��S��ݒ�
		SetCameraScreenCenter(center.intX(), center.intY());

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�̕`��
		_pStage->DrawStage();

		// �v���C���[�̕`��
		for (auto& pll : _pPlayer) {
			pll->Draw();
		}
	}





	// ������
	{
		// �v���C���[1�̃J�����̃Z�b�g
		_pPlayer->CameraSet();

		// �������̂ݕ`��
		SetDrawArea(0, 0, 800, 900);
		SetCameraScreenCenter(400, 450);

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�u���b�N�̕`��
		_pStage->DrawStage();

		// �v���C���[�̕`��
		_pPlayer->Draw();
		_pPlayer1->Draw();
		//_pPlayer2->Draw();
		//_pPlayer3->Draw();
	}

	// �E����
	{
		// �v���C���[2�̃J�����̃Z�b�g
		_pPlayer1->CameraSet();

		// �E�����̂ݕ`��
		SetDrawArea(800, 0, 1600, 900);
		SetCameraScreenCenter(1200, 450);

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�u���b�N�̕`��
		_pStage->DrawStage();

		// �v���C���[�̕`��
		_pPlayer1->Draw();
		//_pPlayer2->Draw();
		//_pPlayer3->Draw();
		_pPlayer->Draw();
	}





	//// ������
	//{
	//	// �v���C���[1�̃J�����̃Z�b�g
	//	_pPlayer->CameraSet();

	//	// �������̂ݕ`��
	//	SetDrawArea(0, 0, 960, 540);
	//	SetCameraScreenCenter(480, 270);

	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();

	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();

	//	// �v���C���[�̕`��
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//}

	//// �E����
	//{
	//	// �v���C���[2�̃J�����̃Z�b�g
	//	_pPlayer1->CameraSet();

	//	// �E�����̂ݕ`��
	//	SetDrawArea(960, 0, 19920, 540);
	//	SetCameraScreenCenter(1440, 270);

	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();

	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();

	//	// �v���C���[�̕`��
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}

	//// �������
	//{
	//	// �v���C���[3�̃J�����̃Z�b�g
	//	_pPlayer2->CameraSet();

	//	// �E�����̂ݕ`��
	//	SetDrawArea(0, 540, 960, 1080);
	//	SetCameraScreenCenter(480, 810);

	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();

	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();

	//	// �v���C���[�̕`��
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}

	//// �E�����
	//{
	//	// �v���C���[4�̃J�����̃Z�b�g
	//	_pPlayer3->CameraSet();

	//	// �E�����̂ݕ`��
	//	SetDrawArea(960, 540, 1920, 1080);
	//	SetCameraScreenCenter(1440, 810);

	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();

	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();

	//	// �v���C���[�̕`��
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
}

VECTOR4 SceneTest::CreateDrawArea(int num) const
{
	return VECTOR4();
}

Vec2 SceneTest::CreateScreenCenter(int num) const
{
	return Vec2();
}

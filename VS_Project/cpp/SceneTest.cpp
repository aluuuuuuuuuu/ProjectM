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
			_pPlayer.push_back(std::make_shared<Player>(_pStageCollisionManager, _pBulletManager, a));
		}
	}

	// �E�B���h�E�̍����ƕ����擾���Ă���
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");

	// �`��͈͂ƃJ�����Z���^�[�̍쐬
	int num = 0;
	for (auto& pl : _pPlayer) {
		_drawArea[num] = CreateDrawArea(num, _windowWidth, _windowHeight);		// �`��͈�
		_cameraSenter[num] = CreateScreenCenter(num, _windowWidth, _windowHeight);	// �J�����̃Z���^�[
		num++;
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
	for (auto& pl : _pPlayer) {
		pl->Update();
	}

	// �o���b�g�̍X�V
	_pBulletManager->Update();
}

void SceneTest::NormalDraw() const
{
	int num = 0;
	for (auto& pl : _pPlayer) {

		// �J�����̃Z�b�g
		pl->CameraSet();

		// �`��͈͂̐ݒ�
		SetDrawArea(_drawArea[num].a, _drawArea[num].b, _drawArea[num].c, _drawArea[num].d);

		// �`���̒��S��ݒ�
		SetCameraScreenCenter(static_cast<float>(_cameraSenter[num].a), static_cast<float>(_cameraSenter[num].b));

		// �o���b�g�̕`��
		_pBulletManager->Draw();

		// �X�e�[�W�̕`��
		_pStage->DrawStage();

		// �v���C���[�̕`��
		for (auto& pll : _pPlayer) {
			pll->Draw();
		}
	}

	//// ������
	//{
	//	// �v���C���[1�̃J�����̃Z�b�g
	//	_pPlayer->CameraSet();
	//
	//	// �������̂ݕ`��
	//	SetDrawArea(0, 0, 800, 900);
	//	SetCameraScreenCenter(400, 450);
	//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
	//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
	//
	//	// �v���C���[�̕`��
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	//_pPlayer2->Draw();
	//	//_pPlayer3->Draw();
	//}
	//
	//// �E����
	//{
	//	// �v���C���[2�̃J�����̃Z�b�g
	//	_pPlayer1->CameraSet();
	//
	//	// �E�����̂ݕ`��
	//	SetDrawArea(800, 0, 1600, 900);
	//	SetCameraScreenCenter(1200, 450);
	//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
	//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
	//
	//	// �v���C���[�̕`��
	//	_pPlayer1->Draw();
	//	//_pPlayer2->Draw();
	//	//_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
	//
	//
	//
	//
	//
	//// ������
	//{
	//	// �v���C���[1�̃J�����̃Z�b�g
	//	_pPlayer->CameraSet();
	//
	//	// �������̂ݕ`��
	//	SetDrawArea(0, 0, 960, 540);
	//	SetCameraScreenCenter(480, 270);
	//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
	//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
	//
	//	// �v���C���[�̕`��
	//	_pPlayer->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//}
	//
	//// �E����
	//{
	//	// �v���C���[2�̃J�����̃Z�b�g
	//	_pPlayer1->CameraSet();
	//
	//	// �E�����̂ݕ`��
	//	SetDrawArea(960, 0, 19920, 540);
	//	SetCameraScreenCenter(1440, 270);
	//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
	//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
	//
	//	// �v���C���[�̕`��
	//	_pPlayer1->Draw();
	//	_pPlayer2->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
	//
	//// �������
	//{
	//	// �v���C���[3�̃J�����̃Z�b�g
	//	_pPlayer2->CameraSet();
//
	//	// �E�����̂ݕ`��
	//	SetDrawArea(0, 540, 960, 1080);
	//	SetCameraScreenCenter(480, 810);
//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
//
	//	// �v���C���[�̕`��
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
//
	//// �E�����
	//{
	//	// �v���C���[4�̃J�����̃Z�b�g
	//	/_pPlayer3->CameraSet();
//
	//	// �E�����̂ݕ`��
	//	SetDrawArea(960, 540, 1920, 1080);
	//	/SetCameraScreenCenter(1440, 810);
//
	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();
//
	//	// �X�e�[�W�u���b�N�̕`��
	//	_pStage->DrawStage();
//
	//	// �v���C���[�̕`��
	//	_pPlayer2->Draw();
	//	_pPlayer1->Draw();
	//	_pPlayer3->Draw();
	//	_pPlayer->Draw();
	//}
}

VECTOR4 SceneTest::CreateDrawArea(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int halfWidth = scWidth / 2;
	int halfHeight = scHeight / 2;

	// �v���C���[�̑����ŏ�����؂�ւ���
	switch (size)
	{
	case 1:
		return VECTOR4{ 0,0,scWidth,scHeight };
		break;
	case 2:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth , scHeight };
		}
		else {
			return VECTOR4{ halfWidth, 0,scWidth ,
							scHeight };
		}
		break;

	case 3:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		break;

	case 4:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else if (num == 2) {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		else {
			return VECTOR4{ halfWidth ,halfHeight ,
							scWidth,scHeight };
		}
		break;
	default:
		return VECTOR4{};
		break;
	}
}

VECTOR2 SceneTest::CreateScreenCenter(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int width;
	int height;

	switch (size)
	{
	case 1:
		return VECTOR2{ scWidth / 2,scHeight / 2 };
		break;

	case 2:

		width = scWidth / 2;
		height = scHeight / 2;

		if (num == 0) {
			return VECTOR2{ width, height };
		}
		else {
			return VECTOR2{ width * 3, height };
		}
		break;

	case 3:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else {
			return VECTOR2{ width, height * 3 };
		}
		break;

	case 4:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else if (num == 2) {
			return VECTOR2{ width, height * 3 };
		}
		else {
			return VECTOR2{ width * 3, height * 3 };
		}
		break;
	default:
		break;
	}
}

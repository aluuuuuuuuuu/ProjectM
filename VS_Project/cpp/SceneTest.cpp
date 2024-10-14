#include "SceneTest.h"
#include "StageManager.h"
#include "Player.h"
#include "StageCollisionManager.h"

SceneTest::SceneTest()
{
	// �e�N���X�̃C���X�^���X�쐬
	{
		_pStage = std::make_shared<StageManager>();	// �X�e�[�W�}�l�[�W���[
		_pPlayer = std::make_shared<Player>();		// �v���C���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);
	}

	// �֐��|�C���^�̏�����
	{
		_updateFunc = &SceneTest::NormalUpdate;
		_drawFunc = &SceneTest::NormalDraw;
	}

	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/PlayerCamera.csv");

	// �J�����̃j�A�t�@�[�̐ݒ�
	DxLib::SetCameraNearFar(std::get<float>(Constants["CAMERA_NEAR"]), std::get<float>(Constants["CAMERA_FAR"]));

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
	SetCameraPositionAndTarget_UpVecY(VECTOR{ 50.0f,32.0f,-96.0f }, VECTOR{ 50,0,0 });

	// �v���C���[�̍X�V����
	_pPlayer->Update();

	// �v���C���[�ƃX�e�[�W�̓����蔻��
	_pPlayer->Position += _pStageCollisionManager->CapsuleCollision(_pPlayer->_data);

	_pPlayer->Set(_pPlayer->Position);
}

void SceneTest::NormalDraw() const
{
	// �O���b�h�̕`��
	//DrawGrid();
	
	// �X�e�[�W�u���b�N�̕`��
	_pStage->DrawStage();

	// �v���C���[�̕`��
	_pPlayer->Draw();
}

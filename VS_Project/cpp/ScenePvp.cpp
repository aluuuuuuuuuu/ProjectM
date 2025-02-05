#include "ScenePvp.h"
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
#include "EffekseerForDXLib.h"

ScenePvp::ScenePvp(PlayerData data):
	_frame(110)
{
	// �^�C�g����BGM���~�߂�
	SoundManager::GetInstance().StopBGM(BGM_OPENING);

	// �e�N���X�̃C���X�^���X�쐬
	{
		_pWedgewormManager = std::make_shared<WedgewormManager>();	// �S���}�l�[�W���[
		_pBulletManager = std::make_shared <BulletManager>(_pBulletCollsionManager, _pWedgewormManager);				// �o���b�g�}�l�[�W���[
		_pStage = std::make_shared<StageManager>();													// �X�e�[�W�}�l�[�W���[
		_pBulletCollsionManager = std::make_shared<MapBulletCollisionManager>(_pStage);				// �o���b�g�R���W�����}�l�[�W���[
		_pStageCollisionManager = std::make_shared<StageCollisionManager>(_pStage);					// �X�e�[�W�R���W�����}�l�[�W���[
		_pPlayerManager = std::make_shared<PlayerManager>(_pStage, _pBulletManager, data);	// �v���C���[�}�l�[�W���[
		_pSkyDome = std::make_shared<SkyDome>();	// �X�J�C�h�[��
		_pGameFlowManager = std::make_shared<GameFlowManager>(_pPlayerManager);	// �Q�[���t���[�}�l�[�W���[
		_pNum = std::make_shared<NumUtility>(0.5f, Vec2{ 734,100 });	// �������[�e�B���e�B
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
		_updateFunc = &ScenePvp::FadeInUpdate;
		_drawFunc = &ScenePvp::FadeInDraw;
	}

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();

	// �X�N���[���̍쐬
	MakeScreen();

}

ScenePvp::~ScenePvp()
{
	// ���C�g�̍폜
	DeleteLightHandleAll();

	// �`��͈͂ƕ`���̒��S�̏�����
	SetDrawArea(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"));
	SetCameraScreenCenter(static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2), static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2));
}

void ScenePvp::Update()
{
	(this->*_updateFunc)();
}

void ScenePvp::Draw() const
{
	(this->*_drawFunc)();
}

void ScenePvp::NormalUpdate()
{
	// BGM���Đ�	
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
		_updateFunc = &ScenePvp::EndUpdate;
		_drawFunc = &ScenePvp::EndDraw;
	}

	// ���Ԃ̍X�V����
	_pNum->Update(_pGameFlowManager->GetGameTime());
}

void ScenePvp::NormalDraw() const
{
	// �v���C���[�̉�ʂ̐������`�悷��
	for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

		// �`���̐ݒ�
		SetDrawScreen(_screen[i]);

		// �X�N���[���̃N���A
		ClearDrawScreen();

		// �J�����̐ݒ�
		SetCameraNearFar(1.0f, 1000.0f);

		_pPlayerManager->CameraSet(i);

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
		_pPlayerManager->Draw(i);
	}

	// �`����߂�
	SetDrawScreen(DX_SCREEN_BACK);

	// �X�N���[���̕`��
	if (_pPlayerManager->GetPlayerNum() == 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(960, 0, _screen[1], true);
	}
	else if (_pPlayerManager->GetPlayerNum() > 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(960, 0, _screen[1], true);
		DrawGraph(0, 540, _screen[2], true);
		DrawGraph(960, 540, _screen[3], true);
	}

	// ���Ԃ̍X�V����
	_pNum->Draw();

}

void ScenePvp::EndUpdate()
{
	// �Q�[���t���[�}�l�[�W���[�̍X�V
	_pGameFlowManager->Update();

	_pPlayerManager->Update();

	_frame++;
	if (_frame >= 110) {

		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	}

	//// �Q�[�����I�����Ă���P�Q�O�t���[�����Ă΃��U���g��ʂֈڍs
	//if (_pGameFlowManager->GetFlameCount() >= 180) {
	//	SoundManager::GetInstance().StopBGM(BGM_BATTLE);
	//	SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	//}
}

void ScenePvp::EndDraw() const
{

	NormalDraw();

	//// �v���C���[�̉�ʂ̐������`�悷��
	//for (int i = 0; i < _pPlayerManager->GetPlayerNum(); i++) {

	//	// �J�����̐ݒ�
	//	_pPlayerManager->CameraSet(i);

	//	// �`��͈͂̐ݒ�
	//	SetDrawArea(_pPlayerManager->GetArea(i).a, _pPlayerManager->GetArea(i).b, _pPlayerManager->GetArea(i).c, _pPlayerManager->GetArea(i).d);

	//	// �`���̒��S��ݒ�
	//	SetCameraScreenCenter(static_cast<float>(_pPlayerManager->GetCenter(i).a), static_cast<float>(_pPlayerManager->GetCenter(i).b));

	//	//�X�J�C�h�[���̕`��
	//	_pSkyDome->Draw();

	//	// �o���b�g�̕`��
	//	_pBulletManager->Draw();

	//	// �X�e�[�W�̕`��
	//	_pStage->DrawStage();

	//	// �S���̕`��
	//	_pWedgewormManager->Draw();
	//	// �v���C���[�̕`��
	//	_pPlayerManager->Draw(i);
	//}
}

void ScenePvp::FadeInUpdate()
{
	// �ʏ�̍X�V
	NormalUpdate();

	_frame--;
	if (_frame == 0) {
		_updateFunc = &ScenePvp::NormalUpdate;
		_drawFunc = &ScenePvp::NormalDraw;
	}
}

void ScenePvp::FadeInDraw() const
{
	// �ʏ�̕`��
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * ((float)_frame / 110));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScenePvp::MakeScreen()
{
	if (_pPlayerManager->GetPlayerNum() == 2) {
		_screen.push_back(DxLib::MakeScreen(960, 1080, true));
		_screen.push_back(DxLib::MakeScreen(960, 1080, true));
	}
	else {
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
		_screen.push_back(DxLib::MakeScreen(960, 540, true));
	}
}

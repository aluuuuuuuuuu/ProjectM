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
#include "PlayerBulletCollisionManager.h"
#include "ItemManager.h"

ScenePvp::ScenePvp(PlayerData data) :
	_frame(Application::GetInstance().GetConstantInt("FRAME_NUM") * 2)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/ScenePvp.csv");

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
		_pNum = std::make_shared<NumUtility>(GetConstantFloat("NUM_SIZE"), Vec2{ GetConstantFloat("NUM_POS_X"),GetConstantFloat("NUM_POS_Y") });	// �������[�e�B���e�B
		_pPlayerBulletCollisionManager = std::make_shared<PlayerBulletCollisionManager>(_pBulletManager, _pPlayerManager);
		_pItemManager = std::make_shared<ItemManager>(_pPlayerManager, _pStage);
	}

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
		SetCameraNearFar(GetConstantFloat("CAMERA_NEAR"), GetConstantFloat("CAMERA_FAR"));

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

		// �A�C�e���̕`��
		_pItemManager->Draw();

		// �v���C���[�̕`��
		_pPlayerManager->Draw(i);

	}

	// �`����߂�
	SetDrawScreen(DX_SCREEN_BACK);

	auto& app = Application::GetInstance();


	// �X�N���[���̕`��
	if (_pPlayerManager->GetPlayerNum() == 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(app.GetConstantInt("SCREEN_WIDTH") / 2, 0, _screen[1], true);
	}
	else if (_pPlayerManager->GetPlayerNum() > 2) {
		DrawGraph(0, 0, _screen[0], true);
		DrawGraph(app.GetConstantInt("SCREEN_WIDTH") / 2, 0, _screen[1], true);
		DrawGraph(0, app.GetConstantInt("SCREEN_HEIGHT") / 2, _screen[2], true);
		DrawGraph(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, _screen[3], true);
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

	// �Q�[�����I�����Ă���2�b���Ă΃��U���g��ʂֈڍs
	if (_frame >= Application::GetInstance().GetConstantInt("FRAME_NUM") * 2) {

		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>(_pPlayerManager->GetPlayerData(), _pGameFlowManager->GetGameTime()));
	}
}

void ScenePvp::EndDraw() const
{
	NormalDraw();
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
	int alpha = static_cast<int>(255 * ((float)_frame / Application::GetInstance().GetConstantInt("FRAME_NUM") * 2));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScenePvp::MakeScreen()
{
	auto& app = Application::GetInstance();

	if (_pPlayerManager->GetPlayerNum() == 2) {
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT"), true));
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT"), true));
	}
	else {
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, true));
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, true));
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, true));
		_screen.push_back(DxLib::MakeScreen(app.GetConstantInt("SCREEN_WIDTH") / 2, app.GetConstantInt("SCREEN_HEIGHT") / 2, true));
	}
}

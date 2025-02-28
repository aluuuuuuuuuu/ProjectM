#include "TutorialManager.h"
#include "BulletManager.h"
#include "StageManager.h"
#include "MapBulletCollisionManager.h"
#include "StageCollisionManager.h"
#include "PlayerManager.h"
#include "SkyDome.h"
#include "WedgewormManager.h"
#include "EffectManager.h"
#include "Input.h"

TutorialManager::TutorialManager() :
	_frame(0),
	_tutorialProgress(GUIDE_CAMERA),
	_endFrag(false)
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

	// �摜�̃��[�h
	{
		// �K�C�h���͂̉摜�̃��[�h
		_guideHandle[GUIDE_CAMERA] = LoadGraph("data/image/GuideCamera.png");
		_guideHandle[GUIDE_MOVE] = LoadGraph("data/image/GuideMove.png");
		_guideHandle[GUIDE_JUMP] = LoadGraph("data/image/GuideJump.png");
		_guideHandle[GUIDE_SHOT] = LoadGraph("data/image/GuideShot.png");

		// �N���A�摜�̃��[�h
		_clearHandle = LoadGraph("data/image/Clear.png");
	}

	// �K�C�h���͂̍��W�̐ݒ�
	_guidePos = Vec2{ 1920 / 2, 200 };

	// �N���A�摜�̍��W�̐ݒ�
	_clearPos = Vec2{ 1920 / 2, 1080 / 2 };

	// �֐��|�C���^�̏�����
	_updateFunc = &TutorialManager::CameraUpdate;
	_drawFunc = &TutorialManager::ShareDraw;

	// �S���̍X�V
	_pWedgewormManager->Update();

	// �v���C���[�̍X�V����
	_pPlayerManager->Update();
}

TutorialManager::~TutorialManager()
{
	// �K�C�h���͂̍폜
	for (int i = 0; i < 5; i++) {
		DeleteGraph(_guideHandle[i]);
	}
}

void TutorialManager::Update()
{
	// �f�t�H���g�̏���
	DefaultUpdate();

	(this->*_updateFunc)();
}

void TutorialManager::Draw() const
{
	(this->*_drawFunc)();
}

void TutorialManager::CameraUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::MoveUpdate;
			_tutorialProgress++;
		}
	}
	// �J�������삪�P�b�ȏ�s��ꂽ��N���A�������s��
	else if(Input::GetInstance().GetStickVectorLength(INPUT_RIGHT_STICK, INPUT_PAD_1) > 5000.0f){

		_frame++;
		if (_frame > 60) {
			_endFrag = true;
			_frame = 0;
			_clearScale = 10.0;
		}
	}
}

void TutorialManager::MoveUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::JumpUpdate;
			_tutorialProgress++;
		}
	}
	// �ړ����삪�P���b�ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > 5000.0f) {

		_frame++;
		if (_frame > 60) {
			_endFrag = true;
			_frame = 0;
			_clearScale = 10.0;
		}
	}
}

void TutorialManager::JumpUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::ShotUpdate;
			_tutorialProgress++;
		}
	}
	// �W�����v���삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
}

void TutorialManager::ShotUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::SelectUpdate;
			_tutorialProgress++;
		}
	}
	// �W�����v���삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsTrigger(INPUT_X, INPUT_PAD_1) || Input::GetInstance().IsTrigger(INPUT_RIGHT_TRIGGER, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
}

void TutorialManager::SelectUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::LastUpdate;
			_tutorialProgress++;
		}
	}
	// �W�����v���삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsTrigger(INPUT_RIGHT_SHOULDER, INPUT_PAD_1) || Input::GetInstance().IsTrigger(INPUT_LEFT_SHOULDER, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = 10.0;
	}
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

	// �K�C�h���͂̕`��
	DrawRotaGraph(_guidePos.intX(), _guidePos.intY(), 1.0, 0.0, _guideHandle[_tutorialProgress], true);

	// �N���A�摜�̕`��
	if (_endFrag) DrawRotaGraph(_clearPos.intX(), _clearPos.intY(), _clearScale, 0.0, _clearHandle, true);
}

bool TutorialManager::ClearFunction()
{
	_clearScale -= 0.5;

	_clearScale = max(1.0, _clearScale);

	// A�{�^���������ꂽ��true��Ԃ�
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1) && _clearScale >= 1.0) {
		return true;
	}
}

void TutorialManager::DefaultUpdate()
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

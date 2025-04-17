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
#include "Application.h"

TutorialManager::TutorialManager() :
	_frame(0),
	_tutorialProgress(GUIDE_CAMERA),
	_endFrag(false),
	_shotCount(0),
	_finishFrag(false)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/TutorialManager.csv");

	_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));


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
		auto& app = Application::GetInstance();
		// ���C�e�B���O���g�p����
		SetUseLighting(true);

		// ���C�g�̃J���[�𒲐�����
		SetLightDifColor(GetColorF(app.GetConstantFloat("LIGHT_COLOR_R"), app.GetConstantFloat("LIGHT_COLOR_G"), app.GetConstantFloat("LIGHT_COLOR_B"), app.GetConstantFloat("LIGHT_COLOR_ALPHA")));

		// ���C�g�̊p�x��ݒ�
		SetLightDirection(VECTOR{ app.GetConstantFloat("LIGHT_DIRECTION_X"), app.GetConstantFloat("LIGHT_DIRECTION_Y") ,app.GetConstantFloat("LIGHT_DIRECTION_Z"), });
	}

	// �摜�̃��[�h
	{
		// �K�C�h���͂̉摜�̃��[�h
		_guideHandle[GUIDE_CAMERA] = LoadGraph("data/image/GuideCamera.png");
		_guideHandle[GUIDE_MOVE] = LoadGraph("data/image/GuideMove.png");
		_guideHandle[GUIDE_JUMP] = LoadGraph("data/image/GuideJump.png");
		_guideHandle[GUIDE_SHOT] = LoadGraph("data/image/GuideShot.png");
		_guideHandle[GUIDE_BOMB] = LoadGraph("data/image/GuideBomb.png");
		_guideHandle[GUIDE_GRAPPLE] = LoadGraph("data/image/GuideGrapple.png");
		_guideHandle[GUIDE_END] = LoadGraph("data/image/GuideEnd.png");
		_guideHandle[GUIDE_RETURN] = LoadGraph("data/image/GuideReturn.png");


		// �N���A�摜�̃��[�h
		_clearHandle = LoadGraph("data/image/Clear.png");

		// �Q�[�������̉摜���[�h
		_explainHandle[0] = LoadGraph("data/image/Story1.png");
		_explainHandle[1] = LoadGraph("data/image/Story2.png");
		_explainHandle[2] = LoadGraph("data/image/Story3.png");
		_explainHandle[3] = LoadGraph("data/image/Story4.png");
		_explainHandle[4] = LoadGraph("data/image/Story5.png");
		_explainHandle[5] = LoadGraph("data/image/Story6.png");
	}

	// �K�C�h���͂̍��W�̐ݒ�
	_guidePos = Vec2{ Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2, GetConstantInt("GUIDE_POS_Y") };

	// �N���A�摜�̍��W�̐ݒ�
	_clearPos = Vec2{ Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2, Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2 };

	// �֐��|�C���^�̏�����
	_updateFunc = &TutorialManager::FirstUpdate;
	_drawFunc = &TutorialManager::FirstDraw;

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

	// �N���A�摜�̍폜
	DeleteGraph(_clearHandle);

	// �Q�[�������̉摜�̍폜
	for (int i = 0; i < 7; i++) {
		DeleteGraph(_explainHandle[i]);
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

bool TutorialManager::GetEndFrag() const
{
	return _finishFrag;
}

void TutorialManager::FirstUpdate()
{
	// �t���[���̉��Z
	_frame++;

	if (7 * MAX_STORY_FRAME < _frame) {

		// �֐��|�C���^�̏�����
		_updateFunc = &TutorialManager::CameraUpdate;
		_drawFunc = &TutorialManager::ShareDraw;
	}
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
	else if (Input::GetInstance().GetStickVectorLength(INPUT_RIGHT_STICK, INPUT_PAD_1) > GetConstantFloat("STICK_DEAD_ZONE")) {

		_frame++;
		if (_frame > Application::GetInstance().GetConstantInt("FRAME_NUM")) {
			_endFrag = true;
			_frame = 0;
			_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
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
	else if (Input::GetInstance().GetStickVectorLength(INPUT_LEFT_STICK, INPUT_PAD_1) > GetConstantFloat("STICK_DEAD_ZONE")) {

		_frame++;
		if (_frame > Application::GetInstance().GetConstantInt("FRAME_NUM")) {
			_endFrag = true;
			_frame = 0;
			_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
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
		_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
	}
}

void TutorialManager::ShotUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			_shotCount = 0;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::BombUpdate;
			_tutorialProgress++;
		}
	}
	// �ˌ����삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsHold(INPUT_RIGHT_TRIGGER, INPUT_PAD_1)) {
		_shotCount++;
	}

	if (_shotCount == Application::GetInstance().GetConstantInt("FRAME_NUM")) {
		_endFrag = true;
		_frame = 0;
		_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
		_shotCount = 0;
	}
}

void TutorialManager::BombUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;
			_shotCount = 0;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::GrappleUpdate;
			_tutorialProgress++;
		}
	}
	// ���e���삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsTrigger(INPUT_Y, INPUT_PAD_1)) {
		_shotCount++;
	}

	if (_shotCount == GetConstantInt("BOMB_COUNT")) {
		_endFrag = true;
		_frame = 0;
		_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
		_shotCount = 0;
	}
}

void TutorialManager::GrappleUpdate()
{
	if (_endFrag) {
		if (ClearFunction()) {
			_frame = 0;
			_endFrag = false;

			// �`���[�g���A����i�߂�
			_updateFunc = &TutorialManager::LastUpdate;
			_drawFunc = &TutorialManager::LastDraw;
			_tutorialProgress++;
		}
	}
	// �O���b�v�����삪���ȏ�s��ꂽ��N���A�������s��
	else if (Input::GetInstance().IsTrigger(INPUT_X, INPUT_PAD_1)) {
		_endFrag = true;
		_frame = 0;
		_clearScale = static_cast<double>(GetConstantFloat("CLEAR_SCALE"));
	}
}

void TutorialManager::LastUpdate()
{
	if (_frame < 240) {
		_lastDrawGraph = _guideHandle[GUIDE_END];
		_frame++;
	}
	else {
		_lastDrawGraph = _guideHandle[GUIDE_RETURN];

		// �X�^�[�g�{�^���ŃZ���N�g��ʂɖ߂�
		if (Input::GetInstance().IsTrigger(INPUT_START, INPUT_PAD_1)) {
			_finishFrag = true;
		}
	}
}

void TutorialManager::FirstDraw() const
{

	// �w�i�������Â�����
	SetDrawBlendMode(DX_BLENDMODE_MULA, 0);
	DrawBox(0, 0, Application::GetInstance().GetConstantInt("SCREEN_WIDTH"), Application::GetInstance().GetConstantInt("SCREEN_HEIGHT"), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

	// �������̕`��
	DrawRotaGraph(_guidePos.intX(), _guidePos.intY(), 1.0, 0.0, _explainHandle[static_cast<int>(_frame / MAX_STORY_FRAME)], true);
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

void TutorialManager::LastDraw() const
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

	// ���͂̕`��
	DrawRotaGraph(_guidePos.intX(), _guidePos.intY(), 1.0, 0.0, _lastDrawGraph, true);
}

bool TutorialManager::ClearFunction()
{
	auto& app = Application::GetInstance();

	_clearScale -= static_cast<double>(GetConstantFloat("CLEAR_SCALE_RATE"));

	_clearScale = max(1.0, _clearScale);

	if (_clearScale == 1.0 && _frame < 30) {
		_clearPos.x = app.GetConstantInt("SCREEN_WIDTH") / static_cast<float>(2) + GetRand(20) - 10;
		_clearPos.y = app.GetConstantInt("SCREEN_HEIGHT") / static_cast<float>(2) + GetRand(20) - 10;
	}

	if (_frame > 30) {
		_clearPos = Vec2{ app.GetConstantInt("SCREEN_WIDTH") / 2,app.GetConstantInt("SCREEN_HEIGHT") / 2 };
	}

	_frame++;
	if (_frame > 90) {
		return true;
	}
	else {
		return false;
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

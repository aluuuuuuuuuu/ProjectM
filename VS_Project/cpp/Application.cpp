#include "Application.h"
#include "DxLib.h"
#include "Constant.h"
#include "SceneManager.h"
#include "Input.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

bool Application::Init()
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Application.csv");

	// �E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(true);

	// �E�B���h�E���̐ݒ�
	DxLib::SetWindowTextDX("ProjectM");

	// ��ʃT�C�Y�̐ݒ�
	SetWindowSize(GetConstantInt("SCREEN_WIDTH"),
		GetConstantInt("SCREEN_HEIGHT"));

	// �𑜓x�̐ݒ�
	SetGraphMode(GetConstantInt("RESOLUTION_WIDTH"),
		GetConstantInt("RESOLUTION_HEIGHT"),
		GetConstantInt("COLOR_BIT"));

	// �w�ʂ̕`����s��Ȃ�
	SetUseBackCulling(true);

	// ���C�e�B���O���g�p����
	SetUseLighting(true);

	// ���C�g�̃J���[�𒲐�����
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	// ���C�g�̊p�x��ݒ�
	SetLightDirection(VECTOR{ 1.0f, -1.0f ,0.0f, });

	// �j�A���X�g�l�C�o�[�@�ŕ`�悷��
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Dxlib�̏�����
	if (DxLib_Init() == -1) return false;

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �o�b�N�o�b�t�@�ɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	// �w�i�F�̐ݒ�
	SetBackgroundColor(100, 100, 255);

	// �J�[�\���̕\���ݒ�
	SetMouseDispFlag(true);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	

	return true;
}

void Application::Run()
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾
	auto& manager = SceneManager::GetInstance();
	int a = 0;
	// �����V�[����ݒ�
	manager.ChangeScene(std::make_shared <SceneSelect>());

	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::GetInstance();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// �t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// Z�o�b�t�@���g�p���ď�������
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		/*�Q�[������*/

		// �X�V����
		input.Update();
		manager.SceneUpdate();

		manager.SceneDraw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// manager�̃t���O�ŃQ�[�����I��������
		if (manager.GetGameEnd()) break;

		// esc�ŏI���i���j
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}

	// �I���������s��
	Terminate();
}

void Application::Terminate()
{
	DxLib_End();    // DX���C�u�����̏I������
}

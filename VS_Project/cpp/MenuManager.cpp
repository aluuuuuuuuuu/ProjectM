#include "MenuManager.h"
#include "DxLib.h"
#include "SelectFinger.h"
#include "Application.h"
#include "MenuButton.h"
#include "MenuCollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SceneTitle.h"

MenuManager::MenuManager(int padNum)
{
	// �萔�t�@�C���̓ǂݍ���
	ReadCSV("data/constant/MenuManager.csv");

	// �]��
	_margin = GetConstantInt("MARGIN");

	// �t���[��
	_frame = GetConstantInt("FRAME");

	// �֐��|�C���^�̏�����
	_updateFunc = &MenuManager::SlideInUpdate;
	_drawFunc = &MenuManager::NormalDraw;

	// �R���W�����}�l�[�W���[�̍쐬
	_pCollisionManager = std::make_shared<MenuCollisionManager>(*this);

	// �I���w�̃|�C���^�̍쐬
	_pFinger = std::make_shared<SelectFinger>(padNum);

	// ��Չ摜�̃��[�h
	_menuBordHandle = LoadGraph("data/image/Bord.png");

	// �w�i�ڂ����摜
	_backHandle = LoadGraph("data/image/backBloom.png");

	// ��Չ摜�̍��W���擾
	_bordPos.x = static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_WIDTH") / 2);
	_bordPos.y = static_cast<float>(Application::GetInstance().GetConstantInt("SCREEN_HEIGHT") / 2);

	// ���ʃ{�^���摜�̃��[�h
	_volumeBGMGraph[ZERO_GRAPH] = LoadGraph("data/image/VolumeZeroBGM.png");
	_volumeBGMGraph[MIN_GRAPH] = LoadGraph("data/image/VolumeMinBGM.png");
	_volumeBGMGraph[MIDDLE_GRAPH] = LoadGraph("data/image/VolumeMiddleBGM.png");
	_volumeBGMGraph[MAX_GRAPH] = LoadGraph("data/image/VolumeMaxBGM.png");

	_volumeSEGraph[ZERO_GRAPH] = LoadGraph("data/image/VolumeZeroSE.png");
	_volumeSEGraph[MIN_GRAPH] = LoadGraph("data/image/VolumeMinSE.png");
	_volumeSEGraph[MIDDLE_GRAPH] = LoadGraph("data/image/VolumeMiddleSE.png");
	_volumeSEGraph[MAX_GRAPH] = LoadGraph("data/image/VolumeMaxSE.png");

	// �e�{�^���̍쐬�Ə����ݒ�
	_pButton[0] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("CANCEL_POS_X"),GetConstantInt("CANCEL_POS_Y") }, Vec2{ GetConstantInt("CANCEL_RANGE_X"),GetConstantInt("CANCEL_RANGE_Y") }, LoadGraph("data/image/Cancel.png"), BATU_BUTTON);
	_pButton[1] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("MANUAL_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("MANUAL_RANGE_X"),GetConstantInt("MANUAL_RANGE_Y") }, LoadGraph("data/image/Manual.png"), MANUAL_BUTTON);
	_pButton[4] = std::make_shared<MenuButton>(Vec2{ _bordPos.intX(),GetConstantInt("END_POS_Y") }, Vec2{ GetConstantInt("END_RANGE_X"),GetConstantInt("END_RANGE_Y") }, LoadGraph("data/image/End.png"), END_BUTTON);

	auto& sound = SoundManager::GetInstance();

	switch (sound.GetVolumeSE())
	{
	case VOLUME_ZERO:
		_pButton[2] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("SE_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("SE_RANGE_X"),GetConstantInt("SE_RANGE_Y") }, _volumeSEGraph[ZERO_GRAPH], SE_BUTTON);
		break;
	case VOLUME_MIN:
		_pButton[2] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("SE_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("SE_RANGE_X"),GetConstantInt("SE_RANGE_Y") }, _volumeSEGraph[MIN_GRAPH], SE_BUTTON);
		break;
	case VOLUME_MIDDLE:
		_pButton[2] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("SE_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("SE_RANGE_X"),GetConstantInt("SE_RANGE_Y") }, _volumeSEGraph[MIDDLE_GRAPH], SE_BUTTON);
		break;
	case VOLUME_MAX:
		_pButton[2] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("SE_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("SE_RANGE_X"),GetConstantInt("SE_RANGE_Y") }, _volumeSEGraph[MAX_GRAPH], SE_BUTTON);
		break;
	default:
		break;
	}

	switch (sound.GetVolumeBGM())
	{
	case VOLUME_ZERO:
		_pButton[3] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("BGM_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("BGM_RANGE_X"),GetConstantInt("BGM_RANGE_Y") }, _volumeBGMGraph[ZERO_GRAPH], BGM_BUTTON);
		break;
	case VOLUME_MIN:
		_pButton[3] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("BGM_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("BGM_RANGE_X"),GetConstantInt("BGM_RANGE_Y") }, _volumeBGMGraph[MIN_GRAPH], BGM_BUTTON);
		break;
	case VOLUME_MIDDLE:
		_pButton[3] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("BGM_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("BGM_RANGE_X"),GetConstantInt("BGM_RANGE_Y") }, _volumeBGMGraph[MIDDLE_GRAPH], BGM_BUTTON);
		break;
	case VOLUME_MAX:
		_pButton[3] = std::make_shared<MenuButton>(Vec2{ GetConstantInt("BGM_POS_X"),_bordPos.intY() }, Vec2{ GetConstantInt("BGM_RANGE_X"),GetConstantInt("BGM_RANGE_Y") }, _volumeBGMGraph[MAX_GRAPH], BGM_BUTTON);
		break;
	default:
		break;
	}

	// ���j���[���J������炷
	SoundManager::GetInstance().RingSE(SE_OPEN_MENU);
}

MenuManager::~MenuManager()
{
	DeleteGraph(_menuBordHandle);
	DeleteGraph(_backHandle);
	for (int i = 0; i < MAX_GRAPH; i++) {
		DeleteGraph(_volumeBGMGraph[i]);
		DeleteGraph(_volumeSEGraph[i]);
	}
}

void MenuManager::Update()
{
	(this->*_updateFunc)();
}

void MenuManager::Draw() const
{
	(this->*_drawFunc)();
}

Vec2 MenuManager::GetPos(int buttonNum)
{
	return _pButton[buttonNum]->GetPos();
}

Vec2 MenuManager::GetRange(int buttonNum)
{
	return _pButton[buttonNum]->GetRange();
}

void MenuManager::NormalUpdate()
{
	// �w�̍X�V����
	_pFinger->Update();

	// B�{�^���������ꂽ��E�B���h�E�����
	if (Input::GetInstance().IsTrigger(INPUT_B, _pFinger->GetPadNum())) {

		// ���j���[����鉹��炷
		SoundManager::GetInstance().RingSE(SE_CLOSE_MENU);

		_updateFunc = &MenuManager::SlideOutUpdate;
	}

	// START�{�^���������ꂽ��E�B���h�E�����
	if (Input::GetInstance().IsTrigger(INPUT_START, _pFinger->GetPadNum())) {

		// ���j���[����鉹��炷
		SoundManager::GetInstance().RingSE(SE_CLOSE_MENU);

		_updateFunc = &MenuManager::SlideOutUpdate;
	}

	// A�{�^���������ꂽ�Ƃ������蔻����Ƃ�
	int button = -1;

	if (_pFinger->IsPushButton(INPUT_A)) {
		button = _pCollisionManager->Collision(_pFinger->GetPos());
	}

	if (button != -1) {
		auto& sound = SoundManager::GetInstance();
		switch (button)
		{
		case BATU_BUTTON:
			// �~�{�^���������ꂽ��E�B���h�E�����
			sound.RingSE(SE_CHARA_CANCEL);
			_updateFunc = &MenuManager::SlideOutUpdate;
			break;
		case MANUAL_BUTTON:
			// �}�j���A���{�^���������ꂽ�瑀������E�B���h�E���J��
			break;
		case SE_BUTTON:
			// �T�E���h�{�^���������ꂽ��O�i�K�ŉ��ʒ��߂��ď���������
			switch (sound.GetVolumeSE())
			{
			case VOLUME_ZERO:
				sound.SetVolumeSE(VOLUME_MIN);
				_pButton[2]->ChangeImage(_volumeSEGraph[MIN_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MIN:
				sound.SetVolumeSE(VOLUME_MIDDLE);
				_pButton[2]->ChangeImage(_volumeSEGraph[MIDDLE_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MIDDLE:
				sound.SetVolumeSE(VOLUME_MAX);
				_pButton[2]->ChangeImage(_volumeSEGraph[MAX_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MAX:
				sound.SetVolumeSE(VOLUME_ZERO);
				_pButton[2]->ChangeImage(_volumeSEGraph[ZERO_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			default:
				break;
			}
			break;
		case BGM_BUTTON:
			// �T�E���h�Ɠ���
			switch (sound.GetVolumeBGM())
			{
			case VOLUME_ZERO:
				sound.SetVolumeBGM(VOLUME_MIN);
				_pButton[3]->ChangeImage(_volumeBGMGraph[MIN_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MIN:
				sound.SetVolumeBGM(VOLUME_MIDDLE);
				_pButton[3]->ChangeImage(_volumeBGMGraph[MIDDLE_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MIDDLE:
				sound.SetVolumeBGM(VOLUME_MAX);
				_pButton[3]->ChangeImage(_volumeBGMGraph[MAX_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			case VOLUME_MAX:
				sound.SetVolumeBGM(VOLUME_ZERO);
				_pButton[3]->ChangeImage(_volumeBGMGraph[ZERO_GRAPH]);
				sound.RingSE(SE_NUM_SELECT);
				break;
			default:
				break;
			}
			break;
		case END_BUTTON:
			// �I���t���O�𗧂Ă�
			_frame = 0;
			_updateFunc = &MenuManager::EndUpdate;
			_drawFunc = &MenuManager::EndDraw;
			break;
		default:
			break;
		}
	}
}

void MenuManager::NormalDraw() const
{
	// �ڂ����̕`��
	DrawGraph(1, 0, _backHandle, true);

	// ��Ղ̕`��
	DrawRotaGraph(_bordPos.intX(), _bordPos.intY() + _margin, 1.0, 0.0, _menuBordHandle, true);

	for (auto& button : _pButton) {
		button->Draw(_margin);
	}

	// �w�̕`��
	_pFinger->Draw();
}

void MenuManager::SlideInUpdate()
{
	// �]���̒���
	if (_margin < 0.0f) {
		_margin += GetConstantInt("SLIDE_IN_SCALE");
		if (_margin > 0) {
			_margin = 0;
		}
	}
	else {
		_updateFunc = &MenuManager::NormalUpdate;
	}

	// �w�̍X�V����
	_pFinger->Update();

}

void MenuManager::SlideOutUpdate()
{
	// �]���̒���
	if (GetConstantInt("MARGIN_MAX") >= _margin) {
		_margin += GetConstantInt("SLIDE_OUT_SCALE");
	}
	else {
		_updateFunc = &MenuManager::FadeOutUpdate;
		_drawFunc = &MenuManager::FadeOutDraw;
	}
}

void MenuManager::FadeOutUpdate()
{
	_frame--;
	if (_frame == 0) {
		SceneManager::GetInstance().PopScene();
	}
}

void MenuManager::FadeOutDraw() const
{
	// �ڂ����̕`��
	int alpha = static_cast<int>(255 * ((float)_frame / GetConstantInt("FRAME")));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawGraph(1, 0, _backHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MenuManager::EndUpdate()
{
	_frame++;
	if (_frame > Application::GetInstance().GetConstantInt("FRAME_NUM")) {
		SoundManager::GetInstance().StopBGM(BGM_BATTLE);
		SceneManager::GetInstance().PopScene();
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>(false));
	}
}


void MenuManager::EndDraw() const
{
	auto& app = Application::GetInstance();

	// �ʏ�̕`��
	NormalDraw();

	// �ڂ����̕`��
	int alpha = static_cast<int>(255 * ((float)_frame / app.GetConstantInt("FRAME_NUM")));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, app.GetConstantInt("SCREEN_WIDTH"), app.GetConstantInt("SCREEN_HEIGHT"), 0x0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

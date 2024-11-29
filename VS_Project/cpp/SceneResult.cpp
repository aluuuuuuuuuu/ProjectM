#include "SceneResult.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneManager.h"
#include "ResultUi.h"
#include "NumUtility.h"

SceneResult::SceneResult(PlayerData data):
	_playerData(data)
{
	_pNum = std::make_shared<NumUtility>(Vec2{165,320});
	_pResultUi = std::make_shared<ResultUi>();
	test = LoadGraph("data/image/a.png");
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update()
{
	// A�{�^���������ꂽ�烊�X�^�[�g
	if (Input::GetInstance().IsTrigger(INPUT_A, INPUT_PAD_1)) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTest>(_playerData));
	}

	// B�{�^���������ꂽ��^�C�g�����
	if (Input::GetInstance().IsTrigger(INPUT_B, INPUT_PAD_1)) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
	}
	
	// START�{�^���������ꂽ�烁�j���[���J��
	if (Input::GetInstance().IsTrigger(INPUT_START, INPUT_PAD_1)) {
		SceneManager::GetInstance().PushScene(std::make_shared<SceneMenu>(INPUT_PAD_1));
	}

	// �����\���̍X�V����
	_pNum->Update(333333);
}

void SceneResult::Draw() const
{
	DrawGraph(0, 0, test, true);
	// ���U���gUI�̕`��
	_pResultUi->Draw();

	// �����̕`��
	_pNum->Draw();

#ifdef _DEBUG
	DrawString(10, 10, "A�{�^���Ń��X�^�[�g", 0xffffff);
	DrawString(10, 40, "B�{�^���Ń^�C�g����ʂ�", 0xffffff);
	DrawString(10, 70, "START�{�^���Ń��j���[", 0xffffff);
#endif // DEBUG
}

#include "GameFlowManager.h"
#include "PlayerManager.h"

GameFlowManager::GameFlowManager(std::shared_ptr<PlayerManager>& plMg) :
	_playerManager(plMg),
	_gameEndFlag(false),
	_frame(0),
	_gameTime(0)
{
}

GameFlowManager::~GameFlowManager()
{
}

void GameFlowManager::Update()
{
	// �v���C���[�̐������𒲂ׂĈ�l�ɂȂ�����I���t���O�𗧂Ă�
	if (_playerManager->GetAreAlivePlayerNum() == 1) {
		_gameEndFlag = true;

		// �����v���C���[���m�肷��
		_playerManager->SetWinner();

	}

	// �Q�[�����I�����Ă���̃t���[�����𐔂���
	if (_gameEndFlag) {
		_frame++;
	}

	// �}�C�t���[���Q�[���^�C�������Z����
	if (!_gameEndFlag) {
		_gameTime++;
	}
}

bool GameFlowManager::GetGameEnd()
{
	return _gameEndFlag;
}

int GameFlowManager::GetFlameCount()
{
	return _frame;
}

int GameFlowManager::GetGameTime()
{
	return _gameTime;
}

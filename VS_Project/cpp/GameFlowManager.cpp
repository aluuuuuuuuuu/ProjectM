#include "GameFlowManager.h"
#include "PlayerManager.h"

GameFlowManager::GameFlowManager(std::shared_ptr<PlayerManager>& plMg):
	_playerManager(plMg),
	_gameEndFlag(false),
	_flame(0)
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
	}

	// �Q�[�����I�����Ă���̃t���[�����𐔂���
	if (_gameEndFlag) {
		_flame++;
	}
}

bool GameFlowManager::GetGameEnd()
{
	return _gameEndFlag;
}

int GameFlowManager::GetFlameCount()
{
	return _flame;
}

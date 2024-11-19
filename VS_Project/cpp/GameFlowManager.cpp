#include "GameFlowManager.h"
#include "PlayerManager.h"

GameFlowManager::GameFlowManager(std::shared_ptr<PlayerManager>& plMg):
	_playerManager(plMg),
	_gameEndFlag(false)
{
}

GameFlowManager::~GameFlowManager()
{
}

void GameFlowManager::Update()
{
	if (_playerManager->GetAreAlivePlayerNum() == 1) {
		_gameEndFlag = true;
	}
}

bool GameFlowManager::GetGameEnd()
{
	return _gameEndFlag;
}

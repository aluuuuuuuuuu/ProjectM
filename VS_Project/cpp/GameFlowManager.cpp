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
	// プレイヤーの生存数を調べて一人になったら終了フラグを立てる
	if (_playerManager->GetAreAlivePlayerNum() == 1) {
		_gameEndFlag = true;
	}

	// ゲームが終了してからのフレーム数を数える
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

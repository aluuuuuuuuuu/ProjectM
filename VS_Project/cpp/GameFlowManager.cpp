#include "GameFlowManager.h"
#include "PlayerManager.h"

GameFlowManager::GameFlowManager(std::shared_ptr<PlayerManager>& plMg) :
	_playerManager(plMg),
	_gameEndFlag(false),
	_flame(0),
	_gameTime(0)
{
	aaa = false;
	if (_playerManager->GetPlayerData().playerNum == PLAYER_ONE) {
		aaa = true;
	}
}

GameFlowManager::~GameFlowManager()
{
}

void GameFlowManager::UpdatePl()
{
	// プレイヤーの生存数を調べて一人になったら終了フラグを立てる
	if (!aaa) {
		if (_playerManager->GetAreAlivePlayerNum() == 1) {
			_gameEndFlag = true;

			// 勝利プレイヤーを確定する
			_playerManager->SetWinner();

		}
	}



	// ゲームが終了してからのフレーム数を数える
	if (_gameEndFlag) {
		_flame++;
	}

	// マイフレームゲームタイムを加算する
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
	return _flame;
}

int GameFlowManager::GetGameTime()
{
	return _gameTime;
}

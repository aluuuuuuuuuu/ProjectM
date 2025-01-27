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
	// �v���C���[�̐������𒲂ׂĈ�l�ɂȂ�����I���t���O�𗧂Ă�
	if (!aaa) {
		if (_playerManager->GetAreAlivePlayerNum() == 1) {
			_gameEndFlag = true;

			// �����v���C���[���m�肷��
			_playerManager->SetWinner();

		}
	}



	// �Q�[�����I�����Ă���̃t���[�����𐔂���
	if (_gameEndFlag) {
		_flame++;
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
	return _flame;
}

int GameFlowManager::GetGameTime()
{
	return _gameTime;
}

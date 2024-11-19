#pragma once
#include <memory>

class PlayerManager;
class GameFlowManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="plMg">�v���C���[�}�l�[�W���[�̎Q��</param>
	GameFlowManager(std::shared_ptr<PlayerManager>& plMg);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~GameFlowManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���I���t���O��Ԃ�
	/// </summary>
	/// <returns>�I�����Ă�����true</returns>
	bool GetGameEnd();

private:
	// �v���C���[�}�l�[�W���[�̎Q��
	std::shared_ptr<PlayerManager>& _playerManager;

	// �Q�[���I���t���O
	bool _gameEndFlag;
};


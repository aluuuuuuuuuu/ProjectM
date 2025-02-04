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

	/// <summary>
	/// �Q�[�����I�����Ă���̃t���[������Ԃ�
	/// </summary>
	/// <returns>�t���[����</returns>
	int GetFlameCount();


	/// <summary>
	/// �Q�[���J�n����̎��Ԃ�Ԃ�
	/// </summary>
	/// <returns>�Q�[���^�C��</returns>
	int GetGameTime();

private:
	// �v���C���[�}�l�[�W���[�̎Q��
	std::shared_ptr<PlayerManager>& _playerManager;

	// �Q�[���I���t���O
	bool _gameEndFlag;

	// �t���[���J�E���^
	int _frame;

	// �Q�[���J�n����̃t���[���𐔂���
	int _gameTime;
};

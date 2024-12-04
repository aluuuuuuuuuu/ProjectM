#pragma once
#include <memory>
#include <vector>
#include "Constant.h"

struct VECTOR4
{
	int a;
	int b;
	int c;
	int d;
};

struct VECTOR2
{
	int a;
	int b;
};

// �v���C���[�̃f�[�^�\���� 
struct PlayerData
{
	// �p�b�h��łǂ̃��f�����g�p���邩
	int charactor[4];

	// �v���C���[�̑���
	int playerNum = 0;

	// ���������v���C���[
	int winner = 0;
};

class StageManager;
class CollisionManager;
class BulletManager;
class Player;
class PlayerManager :
	public Constant
{
public:
	PlayerManager(std::shared_ptr<StageManager>& stageManager, std::shared_ptr<BulletManager>& bullet, PlayerData& data);
	virtual ~PlayerManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(int num) const;

	/// <summary>
	/// �`��͈͂��擾
	/// </summary>
	/// <param name="num">�v���C���[�̃i���o�[</param>
	/// <returns>�v���C���[�̃i���o�[�ɑΉ������`��͈�</returns>
	VECTOR4 GetArea(int num) const;

	/// <summary>
	/// �J�����̃Z���^�[���擾
	/// </summary>
	/// <param name="num">�v���C���[�̃i���o�[</param>
	/// <returns>�v���C���[�̃i���o�[�ɑΉ������J�����̃Z���^�[</returns>
	VECTOR2 GetCenter(int num) const;

	/// <summary>
	/// �v���C���[�̑������擾����
	/// </summary>
	/// <returns>�v���C���[�̑���</returns>
	int GetPlayerNum() const;
	
	/// <summary>
	/// �v���C���[�̃��f���n���h����n��
	/// </summary>
	/// <param name="num">�v���C���[�i���o�[</param>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle(int num) const;

	/// <summary>
	/// �����ɑΉ�����v���C���[�̃J�����̐ݒ�
	/// </summary>
	/// <param name="num">�v���C���[�̃i���o�[</param>
	void CameraSet(int num) const;

	/// <summary>
	/// �������Ă���v���C���[�̐����擾
	/// </summary>
	/// <returns>�������Ă���v���C���[�̐�</returns>
	int GetAreAlivePlayerNum() const;

	/// <summary>
	/// �v���C���[�f�[�^���擾����
	/// </summary>
	PlayerData GetPlayerData() const;

private:

	/// <summary>
	/// �v���C���[������`��͈͂����߂�
	/// </summary>
	/// <param name="num">�v���C���[�̐�-1/param>
	/// <param name="scWidth">�X�N���[���̕�</param>
	/// <param name="scHeight">�X�N���[���̍���</param>
	/// <returns>�`��͈�</returns>
	VECTOR4 CreateDrawArea(int num, int scWidth, int scHeight);

	/// <summary>
	/// �v���C���[������X�N���[���̒��S�����߂�
	/// </summary>
	/// <param name="num">�v���C���[�̐�-1</param>
	/// <param name="scWidth">�X�N���[���̕�</param>
	/// <param name="scHeight">�X�N���[���̍���</param>
	/// <returns>�J�����̒��S</returns>
	VECTOR2 CreateScreenCenter(int num, int scWidth, int scHeight);

	// �v���C���[�̔z��
	std::vector<std::shared_ptr<Player>> _pPlayer;

	// �E�B���h�E�̍���
	int _windowWidth;

	// �E�B���h�E�̕�
	int _windowHeight;

	// �v���C���[�̐��ɑΉ������`��͈�
	VECTOR4 _drawArea[4];

	// �v���C���[�̐��ɑΉ������J�����̃Z���^�[
	VECTOR2 _cameraSenter[4];

	// �v���C���[�̐��̑Ή��������f���n���h��
	int _modelHandle[4];

	// �R���W�����}�l�[�W���[�̃|�C���^
	std::shared_ptr<CollisionManager> _pCollision;

	PlayerData _playerData;
};


#pragma once
#include <memory>
#include <vector>
#include "Constant.h"
#include "BulletManager.h"

constexpr int PLAYER_ONE = 0;
constexpr int PLAYER_TWO = 1;
constexpr int PLAYER_THREE = 2;
constexpr int PLAYER_FORE = 3;

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
	int character[4];

	// �v���C���[�̑���
	int playerNum = -1;

	// ���������v���C���[
	int winner = -1;

	bool aiFlag = false;
};

// �e�̃f�[�^
struct BulletData
{
	// �I�����Ă���e
	int _selectBullet = NORMAL_BULLET;

	// �e���Ƃ̃N�[���^�C��
	int _bullletCoolTime[3];

};

class MyEffect;
class PlayerUi;
class StageManager;
class CollisionManager;
class BulletManager;
class Player;
class PlayerManager :
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stageManager">�X�e�[�W�̎Q��</param>
	/// <param name="bullet">�e�}�l�[�W���[�̎Q��</param>
	/// <param name="data">�v���C���[�f�[�^�̎Q��</param>
	PlayerManager(std::shared_ptr<StageManager>& stageManager, std::shared_ptr<BulletManager>& bullet, PlayerData& data);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="num">�v���C���[�i���o�[</param>
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

	/// <summary>
	/// �����v���C���[��ݒ肷��
	/// </summary>
	void SetWinner();

	/// <summary>
	/// AI��ǉ�����
	/// </summary>
	void AddAi();

	/// <summary>
	/// AI���Ăԗp�̃v���C���[�̍��W��Ԃ��֐�
	/// </summary>
	/// <returns>�v���C���[�̍��W</returns>
	Vec3 GetPlayerPos() const;

	/// <summary>
	/// ai�t���O���擾����
	/// </summary>
	/// <returns>true�ł����AI��</returns>
	bool GetAiFlag() const;

	/// <summary>
	/// AI�L�������폜����
	/// </summary>
	void DeleteAi();

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
	/// <returns>�J�����̒��S</returns>
	VECTOR2 CreateScreenCenter(int num);

	// �v���C���[�̔z��
	std::vector<std::shared_ptr<Player>> _pPlayer;

	// �E�B���h�E�̍���
	int _windowWidth;

	// �E�B���h�E�̕�
	int _windowHeight;

	// �v���C���[�̐��ɑΉ������`��͈�
	VECTOR4 _drawArea[4];

	// �v���C���[�̐��ɑΉ������J�����̃Z���^�[
	VECTOR2 _cameraSenter;

	// �v���C���[�̐��̑Ή��������f���n���h��
	int _modelHandle[4];

	// �v���C���[���Ƃ̒e�̃f�[�^
	BulletData _bulletData[4];

	// �R���W�����}�l�[�W���[�̃|�C���^
	std::shared_ptr<CollisionManager> _pCollision;

	PlayerData _playerData;

	std::shared_ptr<PlayerUi> _pUi;

	// �e�}�l�[�W���[�̎Q��
	std::shared_ptr<BulletManager>& _bulletManager;

	// �����G�t�F�N�g
	std::shared_ptr<MyEffect> _pWinEffect;

	// ���ăG�t�F�N�g
	std::shared_ptr<MyEffect> _pShotOutEffect;

	// �t���[���J�E���^
	int _frame;

	// ���������v���C���[
	int _winner;
};


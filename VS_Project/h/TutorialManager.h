#pragma once
#include <memory>
#include "Vec2.h"
#include "Constant.h"

constexpr int GUIDE_CAMERA = 0;
constexpr int GUIDE_MOVE = 1;
constexpr int GUIDE_JUMP = 2;
constexpr int GUIDE_SHOT = 3;
constexpr int GUIDE_BOMB = 4;
constexpr int GUIDE_GRAPPLE = 5;
constexpr int GUIDE_END = 6;
constexpr int GUIDE_RETURN = 7;

constexpr int MAX_STORY_FRAME = 180;

class WedgewormManager;
class StageManager;
class StageCollisionManager;
class BulletManager;
class MapBulletCollisionManager;
class PlayerManager;
class SkyDome;
class TutorialManager:
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TutorialManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �`���[�g���A�����I��������ǂ�����Ԃ�
	/// </summary>
	/// <returns>true:�I����Ă���</returns>
	bool GetEndFrag() const;


private:

	// �֐��|�C���^
	using _updateFunc_t = void (TutorialManager::*)();
	using _drawFunc_t = void (TutorialManager::*)() const;

	// �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
	_updateFunc_t _updateFunc = nullptr;
	_drawFunc_t  _drawFunc = nullptr;

	void FirstUpdate();

	void CameraUpdate();

	void MoveUpdate();

	void JumpUpdate();

	void ShotUpdate();

	void BombUpdate();

	void GrappleUpdate();

	void LastUpdate();

	void FirstDraw() const;

	void ShareDraw() const;

	void LastDraw() const; 

	/// <summary>
	/// �N���A�����Ƃ��̏���
	/// </summary>
	/// <returns>A�{�^���������ꂽ��true��Ԃ�</returns>
	bool ClearFunction();

	// �f�t�H���g�̏���
	void DefaultUpdate();

	// �X�e�[�W�|�C���^
	std::shared_ptr<StageManager> _pStage;

	// �X�e�[�W�R���W�����}�l�[�W���|�C���^
	std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

	// �o���b�g�}�l�[�W���|�C���^
	std::shared_ptr<BulletManager> _pBulletManager;

	// �o���b�g�R���W�����}�l�[�W���[
	std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

	// �v���C���[�}�l�[�W���[
	std::shared_ptr<PlayerManager> _pPlayerManager;

	// �X�J�C�h�[���|�C���^
	std::shared_ptr<SkyDome> _pSkyDome;

	// �S���}�l�[�W���[
	std::shared_ptr<WedgewormManager> _pWedgewormManager;

	// �t���[���J�E���^
	int _frame;

	// �`���[�g���A���̃K�C�h���͉摜�n���h��
	int _guideHandle[8];

	// �K�C�h���͂̍��W
	Vec2 _guidePos;

	// �`���[�g���A���̐i�s�x
	int _tutorialProgress;

	// �N���A�摜�̍��W
	Vec2 _clearPos;

	// �N���A�摜�̃n���h��
	int _clearHandle;

	// ����̏������s�����t���O
	bool _endFrag;

	// �N���A�摜��Scale
	double _clearScale;

	// �Q�[�������̉摜�n���h��
	int _explainHandle[7];

	// �e���������񐔂̃J�E���g
	int _shotCount;

	// ���ׂẴ`���[�g���A�����I�������t���O
	int _finishFrag;

	int _lastDrawGraph;

};
 
#pragma once
#include <memory>

class WedgewormManager;
class StageManager;
class StageCollisionManager;
class BulletManager;
class MapBulletCollisionManager;
class PlayerManager;
class SkyDome;
class TutorialManager
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


private:

	// �֐��|�C���^
	using _UpdateFunc_t = void (TutorialManager::*)();
	using _DrawFunc_t = void (TutorialManager::*)() const;

	// �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
	_UpdateFunc_t _updateFunc = nullptr;
	_DrawFunc_t  _drawFunc = nullptr;

	void CameraUpdate();

	void MoveUpdate();

	void JumpUpdate();

	void ShotUpdate();

	void SelectUpdate();

	void LastUpdate();

	void ShareDraw() const;

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
};
 
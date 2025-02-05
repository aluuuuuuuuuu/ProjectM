#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>
#include <vector>

class BulletManager;
class NumUtility;
class GameFlowManager;
class WedgewormManager;
class SkyDome;
class PlayerManager;
class MapBulletCollisionManager;
class StageCollisionManager;
class StageManager;
struct PlayerData;
class ScenePve :
	public SceneBase,
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="data">�v���C���[�f�[�^</param>
	ScenePve(PlayerData data);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ScenePve();

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
	using m_updateFunc_t = void (ScenePve::*)();
	using m_drawFunc_t = void (ScenePve::*)() const;
	m_updateFunc_t _updateFunc = nullptr;
	m_drawFunc_t _drawFunc = nullptr;

	/// <summary>
	/// �ʏ�̍X�V����
	/// </summary>
	void NormalUpdate();

	/// <summary>
	/// �ʏ�̕`�揈��
	/// </summary>
	void NormalDraw() const;

	/// <summary>
	/// �Q�[���I�����̍X�V����
	/// </summary>
	void EndUpdate();

	/// <summary>
	/// �Q�[���I�����̕`�揈��
	/// </summary>
	void EndDraw() const;

	/// <summary>
	/// �t�F�[�h�C���X�V����
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// �t�F�[�h�C���`�揈��
	/// </summary>
	void FadeInDraw() const;

	// �Q�[���t���[�}�l�[�W���[
	std::shared_ptr<GameFlowManager> _pGameFlowManager;

	// �v���C���[�}�l�[�W���[
	std::shared_ptr<PlayerManager> _pPlayerManager;

	// �X�e�[�W�}�l�[�W���[
	std::shared_ptr<StageManager> _pStage;

	// �o���b�g�}�l�[�W���[
	std::shared_ptr<BulletManager> _pBulletManager;

	// �o���b�g�R���W�����}�l�[�W���[
	std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

	// �X�e�[�W�R���W�����}�l�[�W���[
	std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

	// �S���}�l�[�W���[
	std::shared_ptr<WedgewormManager> _pWedgewormManager;

	// �X�J�C�h�[��
	std::shared_ptr<SkyDome> _pSkyDome;

	// �������[�e�B���e�B
	std::shared_ptr<NumUtility> _pNum;

	// �t���[���J�E���^
	int _frame;
};


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
	ScenePve(PlayerData& data);

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
	void NomalUpdate();

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
	/// �Q�[���t���[�}�l�[�W���[
	/// </summary>
	std::shared_ptr<GameFlowManager> _pGameFlowManager;

	/// <summary>
	/// �v���C���[�}�l�[�W���[
	/// </summary>
	std::shared_ptr<PlayerManager> _pPlayerManager;

	/// <summary>
	/// �X�e�[�W�}�l�[�W���[
	/// </summary>
	std::shared_ptr<StageManager> _pStage;

	/// <summary>
	/// �o���b�g�}�l�[�W���[
	/// </summary>
	std::shared_ptr<BulletManager> _pBulletManager;

	/// <summary>
	/// �o���b�g�R���W�����}�l�[�W���[
	/// </summary>
	std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

	/// <summary>
	/// �X�e�[�W�R���W�����}�l�[�W���[
	/// </summary>
	std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

	/// <summary>
	/// �S���}�l�[�W���[
	/// </summary>
	std::shared_ptr<WedgewormManager> _pWedgewormManager;

	/// <summary>
	/// �X�J�C�h�[��
	/// </summary>
	std::shared_ptr<SkyDome> _pSkyDome;

	/// <summary>
	/// �������[�e�B���e�B
	/// </summary>
	std::shared_ptr<NumUtility> _pNum;
};


#pragma once
#include "SceneBase.h"
#include <memory>
#include "PlayerManager.h"

class SkyDome;
class ResultCharacter;
class NumUtility;
class ResultUi;
class SceneResult :
	public SceneBase
{
public:


	SceneResult(PlayerData data, int gameTime);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneResult();

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
	using _UpdateFunc_t = void (SceneResult::*)();
	using _DrawFunc_t = void (SceneResult::*)() const;

	// �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
	_UpdateFunc_t _updateFunc = nullptr;
	_DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// �ʏ�̍X�V����
	/// </summary>
	void NormalUpdate();

	/// <summary>
	/// �ʏ�̕`�揈��
	/// </summary>
	void NormalDraw() const;

	/// <summary>
	/// �t�F�[�h�p�̍X�V����
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�p�̕`�揈��
	/// </summary>
	void FadeOutDraw() const;

	// �X�J�C�h�[���@
	std::shared_ptr<SkyDome> _pSkyDome;

	// �������p�|�C���^
	std::shared_ptr<NumUtility> _pNum;

	// ���U���g���S�|�C���^
	std::shared_ptr<ResultUi> _pResultUi;

	// �v���C���[�f�[�^��ێ�����
	PlayerData _playerData;

	// �L�����N�^�[
	std::shared_ptr<ResultCharacter> _pCharacter;

	// �t���[���J�E���^
	int _frame;

	// ���Ƀ��[�h����V�[��
	int _nextScene;
};


#pragma once
#include "SceneBase.h"
#include "PlayerManager.h"
#include <memory>

constexpr int CHARACTOR_1 = 1;
constexpr int CHARACTOR_2 = 2;
constexpr int CHARACTOR_3 = 3;
constexpr int CHARACTOR_4 = 4;

constexpr int PLAYER_1 = 1;
constexpr int PLAYER_2 = 2;
constexpr int PLAYER_3 = 3;
constexpr int PLAYER_4 = 4;

class CharactorSelectManager;
class CharactorCard;
class SelectFinger;
class SceneSelect :
    public SceneBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneSelect();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneSelect();

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
    using _UpdateFunc_t = void (SceneSelect::*)();
    using _DrawFunc_t = void (SceneSelect::*)() const;

    // �C�ӂ̃A�b�v�f�[�g�֐��ϐ��A�h���[�֐��ϐ�
    _UpdateFunc_t _updateFunc = nullptr;
    _DrawFunc_t  _drawFunc = nullptr;

	/// <summary>
	/// �v���C���[���I�����̍X�V����
	/// </summary>
	void PlayerNumSelectUpdate();

	/// <summary>
	/// �v���C���[���I�����̕`�揈��
	/// </summary>
	void PlayerNumSelectDraw() const;

	/// <summary>
	/// �L�����N�^�[�I�����̍X�V����
	/// </summary>
	void CharactorSelectUpdate();

	/// <summary>
	/// �L�����N�^�[�I�����̕`�揈��
	/// </summary>
	void CharactorSelectDraw() const;

	/// <summary>
	/// �t�F�[�h�C���X�V����
	/// </summary>
	void FadeInUpdate();

	/// <summary>
	/// �t�F�[�h�A�E�g�X�V����
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�C���`�揈��
	/// </summary>
	void FadeInDraw	() const;

	/// <summary>
	/// �t�F�[�h�A�E�g�`�揈��
	/// </summary>
	void FadeOutDraw() const;

	// �L�����Z���N�g�}�l�[�W���[
	std::shared_ptr<CharactorSelectManager> _pSelectManager;

	// �t�F�[�h�p�t���[���J�E���^
	int _flame;

	// �Q�[���V�[���ɓn���v���C���[�̃f�[�^
	PlayerData _plData;

	int back;
};


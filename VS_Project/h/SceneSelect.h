#pragma once
#include "SceneBase.h"
#include "PlayerManager.h"
#include <memory>
#include "Vec2.h"

constexpr int CHARACTOR_1 = 1;
constexpr int CHARACTOR_2 = 2;
constexpr int CHARACTOR_3 = 3;
constexpr int CHARACTOR_4 = 4;

class SkyDome;
class SelectUI;
class CharacterSelectManager;
class CharacterCard;
class SelectFinger;
class SceneSelect :
    public SceneBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="num">�v���C���[��</param>
    SceneSelect(int num);

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
	/// �L�����N�^�[�I�����̍X�V����
	/// </summary>
	void CharacterSelectUpdate();

	/// <summary>
	/// �L�����N�^�[�I�����̕`�揈��
	/// </summary>
	void CharacterSelectDraw() const;

	/// <summary>
	/// �t�F�[�h�A�E�g�X�V����
	/// </summary>
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�A�E�g�`�揈��
	/// </summary>
	void FadeOutDraw() const;

	/// <summary>
	/// �X���C�h�C���X�V����
	/// </summary>
	void SlideInUpdate();

	/// <summary>
	/// �X���C�h�C���`�揈��
	/// </summary>
	void SlideInDraw() const;

	/// <summary>
	/// �X���C�h�A�E�g�X�V����
	/// </summary>
	void SlideOutUpdate();

	/// <summary>
	/// �X���C�h�A�E�g�`�揈��
	///	</summary>
	void SlideOutDraw() const;

	// �L�����Z���N�g�}�l�[�W���[
	std::shared_ptr<CharacterSelectManager> _pSelectManager;

	// �X�J�C�h�[���̎Q��
	std::shared_ptr<SkyDome> _pSkyDome;

	// �t�F�[�h�p�t���[���J�E���^
	int _frame;

	// �Q�[���V�[���ɓn���v���C���[�̃f�[�^
	PlayerData _plData;

	// ui�N���X�|�C���^
	std::shared_ptr<SelectUI> _pUi;

	// �X���C�h�摜
	int _slideHandle;

	// �X���C�h�摜�̍��W
	Vec2 _slidePos;

};


#pragma once
#include <memory>
#include "PlayerManager.h"
#include "SceneSelect.h"
#include "Vec2.h"

class CharacterCard;
class SelectFinger;
class CharacterSelectManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="plData">�v���C���[�f�[�^�̎Q��</param>
	CharacterSelectManager(PlayerData& plData);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CharacterSelectManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �J�n�{�^���������ꂽ���ǂ����Ԃ�
	/// </summary>
	/// <returns>�����ꂽ��ture</returns>
	bool GetStart()const;

	/// <summary>
	/// �v���C���[�f�[�^���쐬����
	/// </summary>
	void CreateData();

	/// <summary>
	/// �߂�t���O���擾����
	/// </summary>
	/// <returns>true:�߂�</returns>
	bool GetReturnFlag();

private:

	/// <summary>
	/// �w�ƃJ�[�h���d�Ȃ��Ă��邩���肵���̂��A�J�[�h�̃t���O��ύX����
	/// </summary>
	void FingerFunction();
	
	/// <summary>
	/// finger��A�{�^���������ꂽ�Ƃ��ɃJ�[�h�̏�ɂ��邩���肷��֐�
	/// </summary>
	/// <param name="fing">���肷��finger</param>
	/// <param name="card">���肷��card</param>
	/// <returns>�J�[�h�̏�ɂ����true</returns>
	bool IsFingerOnCard(std::shared_ptr<SelectFinger>& fing, std::shared_ptr<CharacterCard>& card);

	// �w�|�C���^
	std::shared_ptr<SelectFinger>_pFinger[4];

	// �J�[�h�|�C���^
	std::shared_ptr<CharacterCard> _pCard[4];

	// �v���C���[�f�[�^�̎Q��
	PlayerData& _plData;

	// �S�w���I�����I������t���O
	bool _selectFinishFlag;

	// �X�^�[�g�{�^���������ꂽ�t���O
	bool _pushStart;

	// �l���I���ɖ߂�t���O
	bool _returnFlag;

	// �X�^�[�g�{�^���摜�n���h��
	int _startButtonHandle;

	// �X�^�[�g�{�^�����W
	Vec2 _startButtonPos;

	bool _viewStartButtonFlag;
};


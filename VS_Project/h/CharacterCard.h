#pragma once
#include "Vec2.h"
#include <memory>
#include "Constant.h"

class SelectFinger;
class CharacterCard:
	public Constant
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="charNum">�L�����N�^�[�i���o�[</param>
	CharacterCard(int charNum);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CharacterCard();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(std::shared_ptr<SelectFinger>& fing);
	
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// ���g�̑I���t���O�𗧂Ă�
	/// </summary>
	/// <param name="plNum">�ǂ̃v���C���[�ɑI�����ꂽ��</param>
	void SelectCharacter(int plNum);

	/// <summary>
	/// ���g�̑I���t���O��������
	/// </summary>
	/// <param name="plNum">�ǂ̃v���C���[�ɑI���������ꂽ��</param>
	void RejectCharacter(int plNum);

	bool GetSelectFlag();

	bool GetSelectFlag(int plNum);

	/// <summary>
	/// �\�����W���擾����
	/// </summary>
	/// <returns>���W</returns>
	Vec2 GetPos() const;


	/// <summary>
	/// ���g�̃L�����N�^�[�i���o�[��Ԃ�
	/// </summary>
	/// <returns>�L�����N�^�[�i���o�[</returns>
	int GetCharacterNum()const;

private:

	// �J�[�h�摜�n���h��
	int _cardHandle;

	// �I����̃C���[�W�摜�n���h��
	int _cardSelectHandle[4];

	// �ǂ̃v���C���[�ɑI�΂ꂽ���t���O
	bool _selectFlag[4];

	// �J�[�h�`����W
	Vec2 _pos;

	// ���g�̃L�����N�^�[�i���o�[
	int _characterNum;
};


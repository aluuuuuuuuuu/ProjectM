#pragma once
#include "Vec2.h"
#include "vector"

constexpr int CHARACTER_1 = 0;
constexpr int CHARACTER_2 = 1;
constexpr int CHARACTER_3 = 2;
constexpr int CHARACTER_4 = 3;


// �����L�����\����
struct Character
{
	int _handle;
	Vec2 _pos;
	double _angle;
	bool _rotateFlag;
};

class FallCharactor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FallCharactor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FallCharactor();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;	
private:

	// �����L�����̃n���h��
	int _fallCharactorHandle[4];

	// �����L�����̍��W
	Vec2 _fallCharactorPos[4];

	// �����L�����p�̃t���[���J�E���^
	int _fallFlame;

	// ��������L�����N�^�[
	std::vector<Character> _fallCharactors;

};


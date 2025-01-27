#pragma once
#include <memory>
#include "Vec3.h"

class Wedgeworm;
class WedgewormManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WedgewormManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~WedgewormManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �S���̍��W��n��
	/// </summary>
	/// <param name="num">�S���i���o�[</param>
	/// <returns>���W</returns>
	Vec3 GetPos(int num) const;

private:

	// worm�I�u�W�F�N�g�̔z��
	std::shared_ptr<Wedgeworm> _worm[2];
};


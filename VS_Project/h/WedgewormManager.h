#pragma once
#include <memory>

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

private:

	// worm�I�u�W�F�N�g�̔z��
	std::shared_ptr<Wedgeworm> _worm[2];
};


#pragma once
#include <memory>

class StageManager;
class StageCollisionManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageCollisionManager(std::shared_ptr<StageManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~StageCollisionManager();


};


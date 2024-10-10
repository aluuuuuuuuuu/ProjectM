#pragma once
#include <memory>

class StageManager;
class StageCollisionManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageCollisionManager(std::shared_ptr<StageManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~StageCollisionManager();


};


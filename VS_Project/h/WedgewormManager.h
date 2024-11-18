#pragma once
#include <memory>

class Wedgeworm;
class WedgewormManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WedgewormManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~WedgewormManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

private:

	// wormオブジェクトの配列
	std::shared_ptr<Wedgeworm> _worm[2];
};


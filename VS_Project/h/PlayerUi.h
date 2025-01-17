#pragma once

class PlayerUi
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerUi();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerUi();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
private:
};


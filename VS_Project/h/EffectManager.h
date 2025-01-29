#pragma once
#include "Singleton.h"
#include <map>
#include "Vec3.h"

constexpr int NORMAL_BULLET_EFFECT = 0;

constexpr int MAX_EFFECT_NUM = 1;

class EffectManager:
	public Singleton<EffectManager>
{
public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Terminate();

	/// <summary>
	/// エフェクトのハンドルを取得する
	/// </summary>
	/// <param name="effect">エフェクトのキー</param>
	/// <returns>ハンドル取得</returns>
	int& GetEffectHandle(int effect);

private:

	/// <summary>
	/// 指定されたエフェクトをロードする
	/// </summary>
	/// <param name="effect">エフェクトのキー</param>
	void LoadEffect(int effect);

	// エフェクトマップ
	std::map<int, int> _effectMap;
};


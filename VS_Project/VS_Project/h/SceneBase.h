#pragma once
#include "Vec3.h"

class SceneManager;
// シーンの基底クラス、全てのシーンクラスはこれを継承する
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw() const = 0;

protected:
};


#pragma once
#include "Vec3.h"

constexpr int SCENE_TITLE = 1;
constexpr int SCENE_SELECT = 2;
constexpr int SCENE_TEST = 3;
constexpr int SCENE_RESELT = 4;

class SceneManager;
// シーンの基底クラス、全てのシーンクラスはこれを継承する
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};

	// 更新処理
	virtual void UpdatePl() = 0;

	// 描画処理
	virtual void Draw() const = 0;

protected:
};


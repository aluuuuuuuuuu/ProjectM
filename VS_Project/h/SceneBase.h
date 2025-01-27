#pragma once
#include "Vec3.h"

constexpr int SCENE_TITLE = 1;
constexpr int SCENE_SELECT = 2;
constexpr int SCENE_PVP = 3;
constexpr int SCENE_PVE = 4;
constexpr int SCENE_RESELT = 5;

class SceneManager;
// �V�[���̊��N���X�A�S�ẴV�[���N���X�͂�����p������
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};

	// �X�V����
	virtual void Update() = 0;

	// �`�揈��
	virtual void Draw() const = 0;

protected:
};


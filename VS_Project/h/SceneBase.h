#pragma once
#include "Vec3.h"

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


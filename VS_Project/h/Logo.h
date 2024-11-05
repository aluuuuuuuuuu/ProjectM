#pragma once
#include "Vec2.h"
#include <memory>

class SceneTitle;
class Logo
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Logo(SceneTitle& scene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Logo();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

private:
	
	// �\���ʒu
	Vec2 _dispPos;

	// ���S�摜
	int _logo;
};


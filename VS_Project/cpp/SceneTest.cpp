#include "SceneTest.h"
#include "DxLib.h"
#include "Singleton.h"

SceneTest::SceneTest()
{
	
	m_updateFunc = &SceneTest::NormalUpdate;
	m_drawFunc = &SceneTest::NormalDraw;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*m_updateFunc)();
}

void SceneTest::Draw() const
{
	// グリッドの表示
	//DrawGrid();

	(this->*m_drawFunc)();
}

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, L"X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, L"X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, L"Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, L"Z-", 0xffffff);
	}
}

void SceneTest::NormalUpdate()
{
	
}

void SceneTest::NormalDraw() const
{
	
}

void SceneTest::SeqUpdate()
{
	
}

void SceneTest::SeqDraw() const
{
	
}

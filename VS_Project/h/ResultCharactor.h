#pragma once
#include "Components.h"

class ResultCharactor :
	public Model,
	public Animation,
	public Transform
{
public:
	ResultCharactor(int plNum);
	virtual ~ResultCharactor();

	void Update();

	void Draw() const;

private:

	//// アニメーションが終了したタイミングをとるためのフラグ
	//bool _flag;

	//// 演出アニメーションの最大フレームが入る
	//int _maxAnimeFrame;

	//// アニメーションのフレームを増やすか減らすかを判断するフラグ
	//bool _animFlag;

};


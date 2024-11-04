#pragma once
#include "Singleton.h"

class SoundManager:
	public Singleton<SoundManager>
{
public:

	/// <summary>
	/// 初期処理
	/// </summary>
	void Init();

	/// <summary>
	/// オープニングのテーマを再生開始する
	/// </summary>
	void StartOp();

	/// <summary>
	/// オープニングのテーマを再生停止する
	/// </summary>
	void StopOp();

	/// <summary>
	/// タイトル画面でボタンを押したときの音を鳴らす
	/// </summary>
	void RingStartSE();

private:

	// オープニングのテーマ
	int _opBGM;

	// タイトル画面でボタンを押したときの音
	int _startSE;

};


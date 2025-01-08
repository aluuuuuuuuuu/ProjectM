#pragma once
#include "Singleton.h"

#define VOLUME_MIN 85
#define VOLUME_MIDDLE 170
#define VOLUME_MAX 255
#define VOLUME_ZERO 0

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

	/// <summary>
	/// BGMの音量を設定する
	/// </summary>
	/// <param name="volume">音量定数</param>
	void SetVolumeBGM(int volume);

	/// <summary>
	/// SEの音量を設定する
	/// </summary>
	/// <param name="volume">音量定数</param>
	void SetVolumeSE(int volume);

	/// <summary>
	/// BGMの音量を返す
	/// </summary>
	/// <returns>BGMの音量</returns>
	int GetVolumeBGM();

	/// <summary>
	/// SEの音量を返す
	/// </summary>
	/// <returns>SEの音量</returns>
	int GetVolumeSE();

private:

	// オープニングのテーマ
	int _opBGM = 0;

	// タイトル画面でボタンを押したときの音
	int _startSE = 0;

	// BGM音量
	int _volumeBGM = VOLUME_MIDDLE;
	
	// SE音量
	int _volumeSE = VOLUME_MIDDLE;
};


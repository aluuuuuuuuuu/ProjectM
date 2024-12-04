#pragma once
#include <memory>
#include <vector>
#include "Constant.h"

struct VECTOR4
{
	int a;
	int b;
	int c;
	int d;
};

struct VECTOR2
{
	int a;
	int b;
};

// プレイヤーのデータ構造体 
struct PlayerData
{
	// パッド基準でどのモデルを使用するか
	int charactor[4];

	// プレイヤーの総数
	int playerNum = 0;

	// 勝利したプレイヤー
	int winner = 0;
};

class StageManager;
class CollisionManager;
class BulletManager;
class Player;
class PlayerManager :
	public Constant
{
public:
	PlayerManager(std::shared_ptr<StageManager>& stageManager, std::shared_ptr<BulletManager>& bullet, PlayerData& data);
	virtual ~PlayerManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(int num) const;

	/// <summary>
	/// 描画範囲を取得
	/// </summary>
	/// <param name="num">プレイヤーのナンバー</param>
	/// <returns>プレイヤーのナンバーに対応した描画範囲</returns>
	VECTOR4 GetArea(int num) const;

	/// <summary>
	/// カメラのセンターを取得
	/// </summary>
	/// <param name="num">プレイヤーのナンバー</param>
	/// <returns>プレイヤーのナンバーに対応したカメラのセンター</returns>
	VECTOR2 GetCenter(int num) const;

	/// <summary>
	/// プレイヤーの総数を取得する
	/// </summary>
	/// <returns>プレイヤーの総数</returns>
	int GetPlayerNum() const;
	
	/// <summary>
	/// プレイヤーのモデルハンドルを渡す
	/// </summary>
	/// <param name="num">プレイヤーナンバー</param>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle(int num) const;

	/// <summary>
	/// 引数に対応するプレイヤーのカメラの設定
	/// </summary>
	/// <param name="num">プレイヤーのナンバー</param>
	void CameraSet(int num) const;

	/// <summary>
	/// 生存しているプレイヤーの数を取得
	/// </summary>
	/// <returns>生存しているプレイヤーの数</returns>
	int GetAreAlivePlayerNum() const;

	/// <summary>
	/// プレイヤーデータを取得する
	/// </summary>
	PlayerData GetPlayerData() const;

private:

	/// <summary>
	/// プレイヤー数から描画範囲を求める
	/// </summary>
	/// <param name="num">プレイヤーの数-1/param>
	/// <param name="scWidth">スクリーンの幅</param>
	/// <param name="scHeight">スクリーンの高さ</param>
	/// <returns>描画範囲</returns>
	VECTOR4 CreateDrawArea(int num, int scWidth, int scHeight);

	/// <summary>
	/// プレイヤー数からスクリーンの中心を求める
	/// </summary>
	/// <param name="num">プレイヤーの数-1</param>
	/// <param name="scWidth">スクリーンの幅</param>
	/// <param name="scHeight">スクリーンの高さ</param>
	/// <returns>カメラの中心</returns>
	VECTOR2 CreateScreenCenter(int num, int scWidth, int scHeight);

	// プレイヤーの配列
	std::vector<std::shared_ptr<Player>> _pPlayer;

	// ウィンドウの高さ
	int _windowWidth;

	// ウィンドウの幅
	int _windowHeight;

	// プレイヤーの数に対応した描画範囲
	VECTOR4 _drawArea[4];

	// プレイヤーの数に対応したカメラのセンター
	VECTOR2 _cameraSenter[4];

	// プレイヤーの数の対応したモデルハンドル
	int _modelHandle[4];

	// コリジョンマネージャーのポインタ
	std::shared_ptr<CollisionManager> _pCollision;

	PlayerData _playerData;
};


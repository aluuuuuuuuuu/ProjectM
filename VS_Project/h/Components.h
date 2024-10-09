#pragma once
#include "Vec3.h"
#include <vector>
#include <string>
#include <list>

// 座標、拡大、回転を制御する
class Transform
{
public:
	Transform();
	virtual ~Transform();

	// 座標
	Vec3 Position;

	// 拡大
	Vec3 Scale;

	// 回転
	Vec3 Angle;

	Transform& GetTransformInstance();

private:

};

// モデル全般の制御をする
class Model
{
public:
	Model();
	virtual ~Model();

	// 3Dモデル初期処理
	void InitModel(int modelHandle, int textureHandle);
	void InitModel(int modelHandle);
	
	// 3D更新処理
	void UpdateModel(Transform& transform);

	// 3Dモデル描画処理
	void DrawModel() const;

	// モデルハンドルのゲッター
	int GetModelHandle() const;

	// テクスチャのゲッター
	int GetTextureHandle() const;

protected:
	// モデルハンドル
	int ModelHandle = 0;

private:

	// モデルのテクスチャ
	int m_textureHandle = 0;

};

// アニメーションの制御をする
class Animation
{
public:
	Animation();
	virtual ~Animation();

	// アニメーション初期処理
	void InitAnimation(int& modelHandle, int tag, float rate);

	// アニメーション更新処理
	void UpdateAnimation(int& modelHandle);

	// アニメーション変更
	void ChangeAnimation(int& modelHandle, int tag, bool loop,float blendRate);

	// 連続でアニメを切り替えたい場合のアニメーション変更
	void ChangeAnimationConnect(int& modelHandle, int tag1, int tag2, float rate1,float rate2);

	// アニメーション終了フラグを返す
	bool GetEndAnimFlag();

	// 現行のアニメーションタグを返す
	int GetAnimTag();

private:

	// デフォルトのブレンドレート
	float m_defaultRate = 0.0f;

	// コネクト先のブレンドレートを保存する
	float m_rate2 = 0.0f;

	// ブレンドレート
	float m_blendRateSave = 0.0f;

	// 再生時間
	float m_flameCount = 0.0f;

	// 総フレーム数
	float m_maxFlame = 0.0f;

	// アニメーションインデックス
	int m_attachIndex1 = 0;
	int m_attachIndex2 = 0;

	// 再生中のアニメーション
	int m_playAnimation = 0;

	// 連続で再生するアニメーション
	std::vector<int> m_connectAnimation;

	// 連続で再生するアニメーションの進行状況
	int m_animationState = 0;
	
	// 現行のアニメーションタグ
	int m_runTag = 0;

	// ループ再生フラグ
	bool m_loopFlag = false;

	// デフォルトアニメーションタグ
	int m_defaultTag = 0;

	// アニメーションコネクトフラグ
	bool m_connectFlag = false;

	// アニメーションブレンドレート
	float m_blendRate = 0.0f;

	// アニメーション終了フラグ
	bool m_endAnimFlag = true;

};

struct CapsuleData
{
	Vec3 PointA;
	Vec3 PointB;
	float Radius;
};

class CapsuleCollision
{
public:
	CapsuleCollision();
	virtual ~CapsuleCollision();

	// 初期化処理
	void InitCapsule(Vec3 pos, float radius, float height);

	// 有効化
	void Aactivation();

	// 無効化
	void Invalidation();

	// 有効フラグを得る
	bool IsActivation();

	// コリジョンに値をセットする
	void Set(Vec3 pos);

	// コリジョンの高さをセットする
	void SetHeight(float height);

	// 線分間の距離を求める
	float CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const;

	// テスト表示
	void DrawCapsule() const;

	CapsuleData m_data;
private:
	float m_height = 0;
	bool m_valid = true;	// 基本有効化されている
};

class BoxCollision
{
public:
	BoxCollision();
	virtual ~BoxCollision();

	Vec3 Center;
	Vec3 HalfSize;
	std::vector<Vec3> axes;
private:

};

// Effekseerを使ったエフェクトコンポーネント
class Effect
{
public:
	Effect();
	virtual ~Effect();

	// 初期化処理
	void InitEffect();

	// 終了処理
	void TerminateEffect();

	// ハンドルを追加する
	void AddEffect(const char *fileName, float magnification);

private:

	// エフェクトのハンドルを保持するリスト
	std::list<int> m_effectHandleList;

};


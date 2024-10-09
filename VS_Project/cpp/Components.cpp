#include "Components.h"
#include "DxLib.h"
#include <cmath>
#include <algorithm>

// トランスフォーム

Transform::Transform()
{
}

Transform::~Transform()
{
}

Transform& Transform::GetTransformInstance()
{
	return *this;
}

// モデル

Model::Model() :
	ModelHandle(0),
	m_textureHandle(0)
{
}

Model::~Model()
{
	MV1DeleteModel(ModelHandle);
	DeleteGraph(m_textureHandle);

}

void Model::InitModel(int modelHandle, int textureHandle)
{
	ModelHandle = modelHandle;
	m_textureHandle = textureHandle;

	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(ModelHandle, 0, textureHandle, FALSE);
}

void Model::InitModel(int modelHandle)
{
	ModelHandle = modelHandle;
}

void Model::UpdateModel(Transform& transform)
{
	// 変化させる行列
	MATRIX modelMtx;

	// モデルを拡大する
	MATRIX scaleMtx = MGetScale(transform.Scale.VGet());

	// モデルの回転を設定
	MATRIX rotMtx = MGetRotY(transform.Angle.y);

	// 行列を乗算する
	modelMtx = MMult(scaleMtx, rotMtx);

	// モデルの座標を更新する
	MATRIX transMtx = MGetTranslate(transform.Position.VGet());

	// 行列を乗算する
	modelMtx = MMult(modelMtx, transMtx);

	// モデルハンドルに反映
	MV1SetMatrix(ModelHandle, modelMtx);
}

void Model::DrawModel() const
{
	// モデルの描画
	MV1DrawModel(ModelHandle);
}

int Model::GetModelHandle() const
{
	return ModelHandle;
}

int Model::GetTextureHandle() const
{
	return m_textureHandle;
}

// アニメーション

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::InitAnimation(int& modelHandle, int tag, float rate)
{
	m_defaultRate = rate;

	m_defaultTag = tag;

	m_loopFlag = true;

	m_endAnimFlag = false;

	m_attachIndex1 = MV1AttachAnim(modelHandle, tag);
	m_attachIndex2 = MV1AttachAnim(modelHandle, tag);
	m_maxFlame = MV1GetAttachAnimTotalTime(modelHandle, m_attachIndex1);

	// 再生中のアニメーションのタグを保存する
	m_playAnimation = tag;
}

void Animation::UpdateAnimation(int& modelHandle)
{
	// 前のフレームでアニメーションが終了していたらデフォルトに戻す
	if (m_endAnimFlag) {
		ChangeAnimation(modelHandle, m_defaultTag, true, m_defaultRate);
	}

	// 再生時間を進める
	m_flameCount += 0.5f;

	// ブレンドレートを加算していく
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += m_blendRateSave;

		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex1, m_blendRate);
	}

	// 再生時間がアニメーションの総再生時間に達したとき
	if (m_flameCount >= m_maxFlame) {

		// コネクトフラグがtrueだったら次のアニメーションをスタートさせる
		if (m_connectFlag) {
			m_animationState++;
			ChangeAnimation(modelHandle, m_connectAnimation[m_animationState], true, m_rate2);
			m_connectAnimation.clear();
			m_animationState = 0;
		}
		// ループフラグがtrueだったらループさせる
		else if (m_loopFlag) {
			m_flameCount = 0.0f;
		}
		// 完全に終了したらフラグを立てる
		else {
			m_endAnimFlag = true;
		}
	}

	// アニメーション更新
	MV1SetAttachAnimTime(modelHandle, m_attachIndex1, m_flameCount);
}

// アニメーション変更
void Animation::ChangeAnimation(int& modelHandle, int tag, bool loop, float blendRate)
{
	// 再生するアニメーションを変更する
	if (tag != m_playAnimation) {
		// 現行のアニメーションをデタッチする
		MV1DetachAnim(modelHandle, m_attachIndex2);

		// ループフラグを保存
		m_loopFlag = loop;

		// ブレンドレートを変更
		m_blendRateSave = blendRate;

		// 再生時間を最初に戻す
		m_flameCount = 0.0f;

		// 行っていたアニメーションを保存
		m_attachIndex2 = m_attachIndex1;

		// アニメーションを変更
		m_attachIndex1 = MV1AttachAnim(modelHandle, tag);

		// アニメーションのフレーム数を保存
		m_maxFlame = MV1GetAttachAnimTotalTime(modelHandle, m_attachIndex1);

		// 再生中のアニメーションのタグを保存する
		m_playAnimation = tag;

		// アニメーション終了フラグをfalseに
		m_endAnimFlag = false;

		// ブレンドレートを初期化する
		m_blendRate = 0.0f;

		// コネクトフラグを下げる
		m_connectFlag = false;
	}
}

// アニメーションを連続させたいときの変更関数
void Animation::ChangeAnimationConnect(int& modelHandle, int tag1, int tag2, float rate1, float rate2)
{
	m_endAnimFlag = false;
	m_connectAnimation.push_back(tag1);
	m_connectAnimation.push_back(tag2);
	ChangeAnimation(modelHandle, m_connectAnimation[m_animationState], false, rate1);
	m_connectFlag = true;
}

bool Animation::GetEndAnimFlag()
{
	return m_endAnimFlag;
}

int Animation::GetAnimTag()
{
	return m_playAnimation;
}

// カプセル

CapsuleCollision::CapsuleCollision()
{
}

CapsuleCollision::~CapsuleCollision()
{
}

void CapsuleCollision::InitCapsule(Vec3 pos, float radius, float height)
{
	m_data.Radius = radius;
	m_height = height;

	Vec3 vecA = Vec3{ pos.x,pos.y + m_data.Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + m_data.Radius + m_height,pos.z };

	m_data.PointA = vecA;
	m_data.PointB = vecB;
}

void CapsuleCollision::Aactivation()
{
	m_valid = true;
}

void CapsuleCollision::Invalidation()
{
	m_valid = false;
}

bool CapsuleCollision::IsActivation()
{
	return m_valid;
}

void CapsuleCollision::Set(Vec3 pos)
{
	Vec3 vecA = Vec3{ pos.x,pos.y + m_data.Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + m_data.Radius + m_height,pos.z };

	m_data.PointA = vecA;
	m_data.PointB = vecB;
}

void CapsuleCollision::SetHeight(float height)
{
	m_height = height;
}

float CapsuleCollision::CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const
{
	Vec3 d1 = q1 - p1;
	Vec3 d2 = q2 - p2;
	Vec3 r = p1 - p2;
	float a = d1.dot(d1);
	float e = d2.dot(d2);
	float f = d2.dot(r);

	float s, t;
	const float epsilon = static_cast<float>(1e-6);
	float c = d1.dot(r);
	float b = d1.dot(d2);
	float denom = a * e - b * b;

	// マクロを無効化して競合を防ぐ

	if (denom != 0) {
		s = (b * f - c * e) / denom;
	}
	else {
		s = 0.0f;
	}
	s = (std::max)(0.0f, (std::min)(1.0f, s));
	t = (b * s + f) / e;

	if (t < 0.0f) {
		t = 0.0f;
		s = (std::max)(0.0f, (std::min)(1.0f, -c / a));
	}
	else if (t > 1.0f) {
		t = 1.0f;
		s = (std::max)(0.0f, (std::min)(1.0f, (b - c) / a));
	}

	Vec3 closestPoint1 = p1 + d1 * s;
	Vec3 closestPoint2 = p2 + d2 * t;
	return (closestPoint1 - closestPoint2).Length();
}

void CapsuleCollision::DrawCapsule() const
{
	if (m_valid) {
		DrawSphere3D(m_data.PointA.VGet(), m_data.Radius, 4, 0xff0000, 0xff0000, false);
		DrawSphere3D(m_data.PointB.VGet(), m_data.Radius, 4, 0xff0000, 0xff0000, false);

		Vec3 veca = Vec3{ m_data.PointA.x + m_data.Radius,m_data.PointA.y,m_data.PointA.z };
		Vec3 vecb = Vec3{ m_data.PointB.x + m_data.Radius,m_data.PointB.y,m_data.PointB.z };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ m_data.PointA.x - m_data.Radius,m_data.PointA.y,m_data.PointA.z };
		vecb = Vec3{ m_data.PointB.x - m_data.Radius,m_data.PointB.y,m_data.PointB.z };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ m_data.PointA.x ,m_data.PointA.y,m_data.PointA.z + m_data.Radius };
		vecb = Vec3{ m_data.PointB.x ,m_data.PointB.y,m_data.PointB.z + m_data.Radius };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ m_data.PointA.x ,m_data.PointA.y,m_data.PointA.z - m_data.Radius };
		vecb = Vec3{ m_data.PointB.x ,m_data.PointB.y,m_data.PointB.z - m_data.Radius };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);
	}
}

// ボックスコリジョンクラス

BoxCollision::BoxCollision()
{
}

BoxCollision::~BoxCollision()
{
}

// エフェクトクラス

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::InitEffect()
{
}

void Effect::TerminateEffect()
{
}

void Effect::AddEffect(const char* fileName, float magnification)
{
}

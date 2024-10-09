#include "Components.h"
#include "DxLib.h"
#include <cmath>
#include <algorithm>

// �g�����X�t�H�[��

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

// ���f��

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

	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����
	MV1SetTextureGraphHandle(ModelHandle, 0, textureHandle, FALSE);
}

void Model::InitModel(int modelHandle)
{
	ModelHandle = modelHandle;
}

void Model::UpdateModel(Transform& transform)
{
	// �ω�������s��
	MATRIX modelMtx;

	// ���f�����g�傷��
	MATRIX scaleMtx = MGetScale(transform.Scale.VGet());

	// ���f���̉�]��ݒ�
	MATRIX rotMtx = MGetRotY(transform.Angle.y);

	// �s�����Z����
	modelMtx = MMult(scaleMtx, rotMtx);

	// ���f���̍��W���X�V����
	MATRIX transMtx = MGetTranslate(transform.Position.VGet());

	// �s�����Z����
	modelMtx = MMult(modelMtx, transMtx);

	// ���f���n���h���ɔ��f
	MV1SetMatrix(ModelHandle, modelMtx);
}

void Model::DrawModel() const
{
	// ���f���̕`��
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

// �A�j���[�V����

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

	// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
	m_playAnimation = tag;
}

void Animation::UpdateAnimation(int& modelHandle)
{
	// �O�̃t���[���ŃA�j���[�V�������I�����Ă�����f�t�H���g�ɖ߂�
	if (m_endAnimFlag) {
		ChangeAnimation(modelHandle, m_defaultTag, true, m_defaultRate);
	}

	// �Đ����Ԃ�i�߂�
	m_flameCount += 0.5f;

	// �u�����h���[�g�����Z���Ă���
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += m_blendRateSave;

		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(modelHandle, m_attachIndex1, m_blendRate);
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�����Ƃ�
	if (m_flameCount >= m_maxFlame) {

		// �R�l�N�g�t���O��true�������玟�̃A�j���[�V�������X�^�[�g������
		if (m_connectFlag) {
			m_animationState++;
			ChangeAnimation(modelHandle, m_connectAnimation[m_animationState], true, m_rate2);
			m_connectAnimation.clear();
			m_animationState = 0;
		}
		// ���[�v�t���O��true�������烋�[�v������
		else if (m_loopFlag) {
			m_flameCount = 0.0f;
		}
		// ���S�ɏI��������t���O�𗧂Ă�
		else {
			m_endAnimFlag = true;
		}
	}

	// �A�j���[�V�����X�V
	MV1SetAttachAnimTime(modelHandle, m_attachIndex1, m_flameCount);
}

// �A�j���[�V�����ύX
void Animation::ChangeAnimation(int& modelHandle, int tag, bool loop, float blendRate)
{
	// �Đ�����A�j���[�V������ύX����
	if (tag != m_playAnimation) {
		// ���s�̃A�j���[�V�������f�^�b�`����
		MV1DetachAnim(modelHandle, m_attachIndex2);

		// ���[�v�t���O��ۑ�
		m_loopFlag = loop;

		// �u�����h���[�g��ύX
		m_blendRateSave = blendRate;

		// �Đ����Ԃ��ŏ��ɖ߂�
		m_flameCount = 0.0f;

		// �s���Ă����A�j���[�V������ۑ�
		m_attachIndex2 = m_attachIndex1;

		// �A�j���[�V������ύX
		m_attachIndex1 = MV1AttachAnim(modelHandle, tag);

		// �A�j���[�V�����̃t���[������ۑ�
		m_maxFlame = MV1GetAttachAnimTotalTime(modelHandle, m_attachIndex1);

		// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
		m_playAnimation = tag;

		// �A�j���[�V�����I���t���O��false��
		m_endAnimFlag = false;

		// �u�����h���[�g������������
		m_blendRate = 0.0f;

		// �R�l�N�g�t���O��������
		m_connectFlag = false;
	}
}

// �A�j���[�V������A�����������Ƃ��̕ύX�֐�
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

// �J�v�Z��

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

	// �}�N���𖳌������ċ�����h��

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

// �{�b�N�X�R���W�����N���X

BoxCollision::BoxCollision()
{
}

BoxCollision::~BoxCollision()
{
}

// �G�t�F�N�g�N���X

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

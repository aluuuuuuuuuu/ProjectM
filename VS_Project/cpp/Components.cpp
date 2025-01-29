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
	_modelHandle(0),
	m_textureHandle(0)
{
}

Model::~Model()
{
	MV1DeleteModel(_modelHandle);
	DeleteGraph(m_textureHandle);
}

void Model::InitModel(int modelHandle, int textureHandle)
{
	_modelHandle = modelHandle;
	m_textureHandle = textureHandle;

	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����
	MV1SetTextureGraphHandle(_modelHandle, 0, textureHandle, FALSE);
}

void Model::InitModel(int modelHandle)
{
	_modelHandle = modelHandle;
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
	MV1SetMatrix(_modelHandle, modelMtx);
}

void Model::DrawModel() const
{
	// ���f���̕`��
	MV1DrawModel(_modelHandle);
}

int Model::GetModelHandle() const
{
	return _modelHandle;
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
	_defaultRate = rate;

	_defaultTag = tag;

	_loopFlag = true;

	_endAnimFlag = false;

	_attachIndex1 = MV1AttachAnim(modelHandle, tag, -1, true);
	_attachIndex2 = MV1AttachAnim(modelHandle, tag, -1, true);
	_maxFlame = MV1GetAttachAnimTotalTime(modelHandle, _attachIndex1);

	// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
	_playAnimation = tag;
}

void Animation::UpdateAnimation(int& modelHandle, float count)
{
	// �O�̃t���[���ŃA�j���[�V�������I�����Ă�����f�t�H���g�ɖ߂�
	if (_endAnimFlag) {
		ChangeAnimation(modelHandle, _defaultTag, true, _defaultRate);
	}

	// �Đ����Ԃ�i�߂�
	_flameCount += count;

	// �u�����h���[�g�����Z���Ă���
	if (_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex1, 1.0f);
	}
	else {
		_blendRate += _blendRateSave;

		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex2, 1.0f - _blendRate);

		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex1, _blendRate);
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�����Ƃ�
	if (_flameCount >= _maxFlame) {

		// �R�l�N�g�t���O��true�������玟�̃A�j���[�V�������X�^�[�g������
		if (_connectFlag) {
			_animationState++;
			ChangeAnimation(modelHandle, _connectAnimation[_animationState], true, _rate2);
			//_connectAnimation.clear();
			_animationState = 0;

			// �R�l�N�g�t���O��������
			_connectFlag = false;
		}
		// ���[�v�t���O��true�������烋�[�v������
		else if (_loopFlag) {
			_flameCount = 0.0f;
		}
		// ���S�ɏI��������t���O�𗧂Ă�
		else {
			_endAnimFlag = true;
		}
	}

	// �A�j���[�V�����X�V
	int a =MV1SetAttachAnimTime(modelHandle, _attachIndex1, _flameCount);

	int n = 0;
}

void Animation::UpdateAnimationOnce(int& modelHandle, float count)
{

	// �Đ����Ԃ�i�߂�
	_flameCount += count;

	// �u�����h���[�g�����Z���Ă���
	if (_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex1, 1.0f);
	}
	else {
		_blendRate += _blendRateSave;

		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex2, 1.0f - _blendRate);

		MV1SetAttachAnimBlendRate(modelHandle, _attachIndex1, _blendRate);
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�����Ƃ�
	if (_flameCount >= _maxFlame) {

		// �R�l�N�g�t���O��true�������玟�̃A�j���[�V�������X�^�[�g������
		if (_connectFlag) {
			_animationState++;
			ChangeAnimation(modelHandle, _connectAnimation[_animationState], true, _rate2);
			//_connectAnimation.clear();
			_animationState = 0;

			// �R�l�N�g�t���O��������
			_connectFlag = false;
		}
		// ���[�v�t���O��true�������烋�[�v������
		else if (_loopFlag) {
			_flameCount = 0.0f;
		}
		// ���S�ɏI��������t���O�𗧂Ă�
		else {
			_endAnimFlag = true;
		}
	}

	// �A�j���[�V�����X�V
	int a = MV1SetAttachAnimTime(modelHandle, _attachIndex1, _flameCount);

	int n = 0;


}

/// <summary>
/// �A�j���[�V�����ύX
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="tag">�A�j���[�V�����^�O</param>
/// <param name="loop">���[�v�t���O</param>
/// <param name="blendRate">�u�����h���[�g</param>
void Animation::ChangeAnimation(int& modelHandle, int tag, bool loop, float blendRate)
{
	// �Đ�����A�j���[�V������ύX����
	if (tag != _playAnimation) {
		// ���s�̃A�j���[�V�������f�^�b�`����
		MV1DetachAnim(modelHandle, _attachIndex2);

		// ���[�v�t���O��ۑ�
		_loopFlag = loop;

		// �u�����h���[�g��ύX
		_blendRateSave = blendRate;

		// �Đ����Ԃ��ŏ��ɖ߂�
		_flameCount = 0.0f;

		// �s���Ă����A�j���[�V������ۑ�
		_attachIndex2 = _attachIndex1;

		// �A�j���[�V������ύX
		_attachIndex1 = MV1AttachAnim(modelHandle, tag);

		// �A�j���[�V�����̃t���[������ۑ�
		_maxFlame = MV1GetAttachAnimTotalTime(modelHandle, _attachIndex1);

		// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
		_playAnimation = tag;

		// �A�j���[�V�����I���t���O��false��
		_endAnimFlag = false;

		// �u�����h���[�g������������
		_blendRate = 0.0f;
	}
}

// �A�j���[�V������A�����������Ƃ��̕ύX�֐�
void Animation::ChangeAnimationConnect(int& modelHandle, int tag1, int tag2, float rate1, float rate2)
{
	_endAnimFlag = false;
	_connectAnimation.push_back(tag1);
	_connectAnimation.push_back(tag2);
	ChangeAnimation(modelHandle, _connectAnimation[_animationState], false, rate1);
	_connectFlag = true;
}

bool Animation::GetEndAnimFlag()
{
	return _endAnimFlag;
}

int Animation::GetAnimTag()
{
	return _playAnimation;
}

int Animation::GetAnimeFlame()
{
	return static_cast<int>(_flameCount);
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
	_data.Radius = radius;
	_height = height;

	Vec3 vecA = Vec3{ pos.x,pos.y + _data.Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + _data.Radius + _height,pos.z };

	_data.PointA = vecA;
	_data.PointB = vecB;
}

void CapsuleCollision::Aactivation()
{
	_valid = true;
}

void CapsuleCollision::Invalidation()
{
	_valid = false;
}

bool CapsuleCollision::IsActivation()
{
	return _valid;
}

void CapsuleCollision::Set(Vec3 pos)
{
	// ���W��ۑ����Ă���
	_data.FrontPointA = _data.PointA;
	_data.FrontPointB = _data.PointB;

	// �V�������W���Z�b�g����
	Vec3 vecA = Vec3{ pos.x,pos.y + _data.Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + _data.Radius + _height,pos.z };

	_data.PointA = vecA;
	_data.PointB = vecB;
}

void CapsuleCollision::SetHeight(float height)
{
	_height = height;
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
	if (_valid) {
		DrawCapsule3D(_data.PointA.VGet(), _data.PointB.VGet(), _data.Radius, 4, 0xff0000, 0xff0000, false);
	}
}

// �{�b�N�X�R���W�����N���X

BoxCollision::BoxCollision()
{
}

BoxCollision::~BoxCollision()
{
}


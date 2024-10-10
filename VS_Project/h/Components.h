#pragma once
#include "Vec3.h"
#include <vector>
#include <string>
#include <list>

// ���W�A�g��A��]�𐧌䂷��
class Transform
{
public:
	Transform();
	virtual ~Transform();

	// ���W
	Vec3 Position;

	// �g��
	Vec3 Scale;

	// ��]
	Vec3 Angle;

	Transform& GetTransformInstance();

private:

};

// ���f���S�ʂ̐��������
class Model
{
public:
	Model();
	virtual ~Model();

	// 3D���f����������
	void InitModel(int modelHandle, int textureHandle);
	void InitModel(int modelHandle);
	
	// 3D�X�V����
	void UpdateModel(Transform& transform);

	// 3D���f���`�揈��
	void DrawModel() const;

	// ���f���n���h���̃Q�b�^�[
	int GetModelHandle() const;

	// �e�N�X�`���̃Q�b�^�[
	int GetTextureHandle() const;

protected:
	// ���f���n���h��
	int ModelHandle = 0;

private:

	// ���f���̃e�N�X�`��
	int m_textureHandle = 0;

};

// �A�j���[�V�����̐��������
class Animation
{
public:
	Animation();
	virtual ~Animation();

	// �A�j���[�V������������
	void InitAnimation(int& modelHandle, int tag, float rate);

	// �A�j���[�V�����X�V����
	void UpdateAnimation(int& modelHandle);

	// �A�j���[�V�����ύX
	void ChangeAnimation(int& modelHandle, int tag, bool loop,float blendRate);

	// �A���ŃA�j����؂�ւ������ꍇ�̃A�j���[�V�����ύX
	void ChangeAnimationConnect(int& modelHandle, int tag1, int tag2, float rate1,float rate2);

	// �A�j���[�V�����I���t���O��Ԃ�
	bool GetEndAnimFlag();

	// ���s�̃A�j���[�V�����^�O��Ԃ�
	int GetAnimTag();

private:

	// �f�t�H���g�̃u�����h���[�g
	float _defaultRate = 0.0f;

	// �R�l�N�g��̃u�����h���[�g��ۑ�����
	float _rate2 = 0.0f;

	// �u�����h���[�g
	float _blendRateSave = 0.0f;

	// �Đ�����
	float _flameCount = 0.0f;

	// ���t���[����
	float _maxFlame = 0.0f;

	// �A�j���[�V�����C���f�b�N�X
	int _attachIndex1 = 0;
	int _attachIndex2 = 0;

	// �Đ����̃A�j���[�V����
	int _playAnimation = 0;

	// �A���ōĐ�����A�j���[�V����
	std::vector<int> _connectAnimation;

	// �A���ōĐ�����A�j���[�V�����̐i�s��
	int _animationState = 0;
	
	// ���s�̃A�j���[�V�����^�O
	int m_runTag = 0;

	// ���[�v�Đ��t���O
	bool _loopFlag = false;

	// �f�t�H���g�A�j���[�V�����^�O
	int _defaultTag = 0;

	// �A�j���[�V�����R�l�N�g�t���O
	bool _connectFlag = false;

	// �A�j���[�V�����u�����h���[�g
	float _blendRate = 0.0f;

	// �A�j���[�V�����I���t���O
	bool _endAnimFlag = true;

};

struct CapsuleData
{
	// ���a
	float Radius;

	// ���t���[���̍��W
	Vec3 PointA;
	Vec3 PointB;

	// �O�t���[���̍��W
	Vec3 FrontPointA;
	Vec3 FrontPointB;
};

class CapsuleCollision
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CapsuleCollision();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CapsuleCollision();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="radius">���a</param>
	/// <param name="height">����</param>
	void InitCapsule(Vec3 pos, float radius, float height);

	/// <summary>
	/// �L����
	/// </summary>
	void Aactivation();

	/// <summary>
	/// ������
	/// </summary>
	void Invalidation();

	/// <summary>
	/// �L���t���O���擾����
	/// </summary>
	/// <returns>�L���ł����true</returns>
	bool IsActivation();

	/// <summary>
	/// �R���W�����ɒl���Z�b�g����
	/// </summary>
	/// <param name="pos">���W</param>
	void Set(Vec3 pos);

	/// <summary>
	/// �R���W�����̍������Z�b�g����
	/// </summary>
	/// <param name="height">����</param>
	void SetHeight(float height);

	/// <summary>
	/// �����Ԃ̋��������߂�
	/// </summary>
	/// <param name="p1">����1�̏�_</param>
	/// <param name="q1">����1�̉��_</param>
	/// <param name="p2">����2�̏�_</param>
	/// <param name="q2">����2�̉��_</param>
	/// <returns>����</returns>
	float CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const;

	/// <summary>
	/// �J�v�Z����\������
	/// </summary>
	void DrawCapsule() const;

	CapsuleData _data;
private:
	float m_height = 0;
	bool m_valid = true;	// ��{�L��������Ă���
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

// Effekseer���g�����G�t�F�N�g�R���|�[�l���g
class Effect
{
public:
	Effect();
	virtual ~Effect();

	// ����������
	void InitEffect();

	// �I������
	void TerminateEffect();

	// �n���h����ǉ�����
	void AddEffect(const char *fileName, float magnification);

private:

	// �G�t�F�N�g�̃n���h����ێ����郊�X�g
	std::list<int> m_effectHandleList;

};


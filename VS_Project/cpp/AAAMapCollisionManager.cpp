#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#include ""

MapCollisionManager::MapCollisionManager(CapsuleData& cap, StaticObjectManager& manager) :
	m_playerCapsule(cap),
	m_staticObjectManager(manager)
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Collision.csv");
}

MapCollisionManager::~MapCollisionManager()
{

}

Vec3 MapCollisionManager::PlayerCollision()
{
	// �ړ��x�N�g��������������
	m_lastMoveVec = 0;
	m_move.clear();


	// �v���C���[�ƃI�u�W�F�N�g�̓����蔻����Ƃ�
	for (auto obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// �I�u�W�F�N�g�̎�ނ���肷��
		if (obj->m_code == WALL_CODE) {

			// �p�x�ɉ����ă{�b�N�X�̍ŏ��l�ƍő�l���쐬����
			Vec3 min;
			Vec3 max;
			if (obj->Angle.y == 0.0f) {
				// �{�b�N�X�̍ŏ��l�ƍő�l���쐬����
				min = Vec3{ pos.x - std::get<float>(Constants["WALL_SHORT"]),pos.y,pos.z - std::get<float>(Constants["WALL_LONG"]) };
				max = Vec3{ pos.x + std::get<float>(Constants["WALL_SHORT"]),pos.y + std::get<float>(Constants["WALL_HEIGHT"]),pos.z + std::get<float>(Constants["WALL_LONG"]) };
			}
			else {
				// �{�b�N�X�̍ŏ��l�ƍő�l���쐬����
				min = Vec3{ pos.x - std::get<float>(Constants["WALL_LONG"]),pos.y,pos.z - std::get<float>(Constants["WALL_SHORT"]) };
				max = Vec3{ pos.x + std::get<float>(Constants["WALL_LONG"]),pos.y + std::get<float>(Constants["WALL_HEIGHT"]),pos.z + std::get<float>(Constants["WALL_SHORT"]) };
			}

			// ���肷��
			if (ColliosionBoxCapsuleParallel(min, max)) {
				// �������Ă���

				// ����O�ւ̈ړ��x�N�g�����쐬���ĕۑ�
				m_move.push_back(CollisionMove(min, max));
			}
			else {
				// �������Ă��Ȃ�
			}
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}

	// �ۑ��������ׂĂ̈ړ��x�N�g���𑫂��čŏI�I�Ȉړ��x�N�g�����쐬����
	for (auto vec : m_move) {
		m_lastMoveVec += vec;
	}

	// �J�v�Z���̃f�[�^��ۑ����Ă���
	m_beforePlayerPos = m_playerCapsule;

	return m_lastMoveVec;
}

void MapCollisionManager::DrawColl()
{
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// �I�u�W�F�N�g�̎�ނ���肷��
		if (obj->m_code == WALL_CODE) {
			DrawBoxColl(Vec3(pos.x - std::get<float>(Constants["WALL_LONG"]), pos.y, pos.z - std::get<float>(Constants["WALL_SHORT"])),
				Vec3(pos.x + std::get<float>(Constants["WALL_LONG"]), pos.y + std::get<float>(Constants["WALL_HEIGHT"]), pos.z + std::get<float>(Constants["WALL_SHORT"])));
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}
}

void MapCollisionManager::DrawBoxColl(Vec3 min, Vec3 max)
{
	// �ŏ��l����y��
	DrawLine3D(min.VGet(), VECTOR{ min.x,max.y,min.z }, 0xff0000);

	// �ŏ��l����x��
	DrawLine3D(min.VGet(), VECTOR{ max.x,min.y,min.z }, 0xff0000);

	// �ŏ��l����z��
	DrawLine3D(min.VGet(), VECTOR{ min.x,min.y,max.z }, 0xff0000);

	// �ő�l����y��
	DrawLine3D(max.VGet(), VECTOR{ max.x,min.y,max.z }, 0xff0000);

	// �ő�l����x��
	DrawLine3D(max.VGet(), VECTOR{ min.x,max.y,max.z }, 0xff0000);

	// �ő�l����z��
	DrawLine3D(max.VGet(), VECTOR{ max.x,max.y,min.z }, 0xff0000);
}

bool MapCollisionManager::ColliosionBoxCapsuleParallel(Vec3 min, Vec3 max)
{
	// �l�p�`�̒��Ńv���C���[�̒��S�ɍł��߂��_���v�Z
	float closestX = (std::max)(min.x, (std::min)(m_playerCapsule.PointA.x, max.x));
	float closestY = (std::max)(min.z, (std::min)(m_playerCapsule.PointA.z, max.z));

	// �v���C���[�̒��S�ƍł��߂��_�Ƃ̋������v�Z
	float distanceX = m_playerCapsule.PointA.x - closestX;
	float distanceY = m_playerCapsule.PointA.z - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

	// �������v���C���[�̔��a�ȓ������m�F
	return distanceSquared <= (m_playerCapsule.Radius * m_playerCapsule.Radius);
}

Vec3 MapCollisionManager::CollisionMove(Vec3 min, Vec3 max)
{
	// �����钼�O�Ƀv���C���[�����ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
	// �l�p�`�̒��Œ��O�̃v���C���[�̒��S�ɍł��߂��_���v�Z
	float closestX = (std::max)(min.x, (std::min)(m_beforePlayerPos.PointA.x, max.x));
	float closestY = (std::max)(min.z, (std::min)(m_beforePlayerPos.PointA.z, max.z));

	// �ŋߓ_����v���C���[�̒��S�֌������P�ʃx�N�g�����쐬����
	Vec3 center = (Vec3{ m_beforePlayerPos.PointA.x,0.0f,m_beforePlayerPos.PointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized();

	// �ŋߓ_����v���C���[�̍��W�ւ̋��������߂�
	float length = (Vec3{ m_playerCapsule.PointA.x,0.0f,m_playerCapsule.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

	// ���a����O���W�ւ̋������������l���߂荞�񂾕��̋����ɂȂ�
	length = m_playerCapsule.Radius - length;

	// �ŋߓ_����{�b�N�X�̔���O�ւ̈ړ��x�N�g�����쐬
	return center * length;

}





















// ������\������\����
struct LineSegment {
	Vector3 start, end;

	// �R���X�g���N�^
	LineSegment() : start(Vector3()), end(Vector3()) {}
	LineSegment(const Vector3& start_, const Vector3& end_) : start(start_), end(end_) {}

	// ������̍ŋߐړ_���v�Z
	Vector3 closestPointTo(const Vector3& point) const {
		Vector3 lineVec = end - start;
		Vector3 pointVec = point - start;
		float t = lineVec.dot(pointVec) / lineVec.lengthSquared();

		// t��0����1�͈͓̔��Ɏ��܂�悤�ɂ���
		t = std::max(0.0f, std::min(1.0f, t));
		return start + lineVec * t;
	}
};

// �J�v�Z����\������\����
struct Capsule {
	LineSegment lineSegment; // ���S����
	float radius;            // �J�v�Z���̔��a

	// �R���X�g���N�^
	Capsule(const LineSegment& segment, float radius_) : lineSegment(segment), radius(radius_) {}
};

// AABB�iAxis-Aligned Bounding Box�j��\������\����
struct AABB {
	Vector3 min, max; // �ŏ��_�ƍő�_

	// �R���X�g���N�^
	AABB(const Vector3& min_, const Vector3& max_) : min(min_), max(max_) {}
};

// AABB��̍ŋߐړ_�����߂�֐�
Vector3 ClosestPointOnAABB(const AABB& aabb, const Vector3& point) {
	Vector3 closestPoint;
	// X���ɂ��Ĕ���
	closestPoint.x = std::max(aabb.min.x, std::min(point.x, aabb.max.x));
	// Y���ɂ��Ĕ���
	closestPoint.y = std::max(aabb.min.y, std::min(point.y, aabb.max.y));
	// Z���ɂ��Ĕ���
	closestPoint.z = std::max(aabb.min.z, std::min(point.z, aabb.max.z));
	return closestPoint;
}

// ������AABB�̍ŒZ�������v�Z����֐�
float DistanceSquaredLineSegmentAABB(const LineSegment& segment, const AABB& aabb) {
	// �ŏ�������2���������
	float minDistSq = FLT_MAX;

	// AABB���ɐ����̈�_���܂܂�Ă��邩�`�F�b�N
	Vector3 closestPointStart = ClosestPointOnAABB(aabb, segment.start);
	Vector3 closestPointEnd = ClosestPointOnAABB(aabb, segment.end);

	// �����̊J�n�_��AABB���ɂ���ꍇ
	if (closestPointStart.x == segment.start.x &&
		closestPointStart.y == segment.start.y &&
		closestPointStart.z == segment.start.z) {
		return 0.0f; // �����̓[��
	}

	// �����̏I���_��AABB���ɂ���ꍇ
	if (closestPointEnd.x == segment.end.x &&
		closestPointEnd.y == segment.end.y &&
		closestPointEnd.z == segment.end.z) {
		return 0.0f; // �����̓[��
	}

	// �����̊e�[�_����AABB�ւ̋������v�Z
	float distSqStart = (segment.start - closestPointStart).lengthSquared();
	float distSqEnd = (segment.end - closestPointEnd).lengthSquared();
	minDistSq = std::min(distSqStart, distSqEnd);

	// ������̑��̓_�ɂ��Ă��`�F�b�N
	// ��ʓI�ɂ́AAABB �̊e�ʂɑ΂�������̍ŋߐړ_���v�Z����K�v������܂��B
	// �����ł͊ȗ����̂��߁A�[�_�݂̂��`�F�b�N���Ă��܂��B
	// ��萳�m�ȋ��������߂�ɂ́A�e�ʂƂ̌������`�F�b�N����K�v������܂��B

	return minDistSq;
}

// �J�v�Z����AABB�̓����蔻����s���֐�
bool CheckCapsuleAABB(const Capsule& capsule, const AABB& aabb) {
	// �J�v�Z���̐�����AABB�Ƃ̍ŒZ������2����v�Z
	float distanceSquared = DistanceSquaredLineSegmentAABB(capsule.lineSegment, aabb);

	// �������J�v�Z���̔��a�ȓ����ǂ����𔻒�
	return distanceSquared <= (capsule.radius * capsule.radius);
}
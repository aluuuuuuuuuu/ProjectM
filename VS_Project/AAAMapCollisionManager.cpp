#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#include <algorithm>

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
	Vec3 center =  (Vec3{ m_beforePlayerPos.PointA.x,0.0f,m_beforePlayerPos.PointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized()  ;

	// �ŋߓ_����v���C���[�̍��W�ւ̋��������߂�
	float length = (Vec3{ m_playerCapsule.PointA.x,0.0f,m_playerCapsule.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

	// ���a����O���W�ւ̋������������l���߂荞�񂾕��̋����ɂȂ�
	length = m_playerCapsule.Radius - length;

	// �ŋߓ_����{�b�N�X�̔���O�ւ̈ړ��x�N�g�����쐬
	return center * length;

}

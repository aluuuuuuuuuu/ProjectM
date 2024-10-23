#include "StageCollisionManager.h"
#include "StageManager.h"
#include <algorithm>
#include "Vec2.h"

StageCollisionManager::StageCollisionManager(std::shared_ptr<StageManager>& stage) :
	_pStage(stage)
{
	
}

StageCollisionManager::~StageCollisionManager()
{
}

bool CompareByDist(const ColData& a, const ColData& b)
{
	return a.dist < b.dist; // value ����ɏ��������ɕ��בւ���
}

Vec3 StageCollisionManager::CapsuleCollision(CapsuleData data)
{
	//testFlag = false;
	// �ړ��x�N�g��������������
	_vResultMove = 0;
	_vAllColldata.clear();
	_vAllMove.clear();

	Vec3 max, min;// �ő���W,�ŏ����W

	// �J�v�Z���ƃX�e�[�W�̓����蔻������
	for (int a = 0; a < BLOCK_NUM_X; a++) {
		for (int b = 0; b < BLOCK_NUM_Y; b++) {
			for (int c = 0; c < BLOCK_NUM_Z; c++) {

				// �Ώۂ̃{�b�N�X�����݂����ꍇ�̂ݔ��肷��
				if (_pStage->GetStageInfo(a, b, c) != 0) {

					// �{�b�N�X�̍ő���W�ƍŏ����W�����߂�
					Vec3 vec = { a,b,c };
					max = Vec3{ vec * _pStage->GetConstantInt("BLOCK_SIZE")};
					min = Vec3{ max - _pStage->GetConstantInt("BLOCK_SIZE") };

					// �߂荞��ł��邩�ǂ������肷��
					if (CollisionBoxCapsule(max, min, data)) {

						// ���炷���̈ړ��x�N�g�����쐬
						ColData colData = CreateMoveVector(max, min, data);

						// �z��ɕۑ�
						_vAllColldata.push_back(colData);

						data.PointA += colData.moveVec;
						data.PointB += colData.moveVec;

						data.FrontPointA += colData.moveVec;
						data.FrontPointB += colData.moveVec;

					}
				}
			}
		}
	}	

	// �ۑ������S�Ă̈ړ��x�N�g���𑫂��čŏI�I�Ȉړ��x�N�g�����쐬����
	for (auto& vec : _vAllColldata) {
		_vResultMove += vec.moveVec;
	}

	// �ŏI�I�Ȉړ��x�N�g����Ԃ�
	return _vResultMove;
}

bool StageCollisionManager::CollisionBoxCapsule(Vec3 max, Vec3 min, CapsuleData data)
{
	// �J�v�Z���̐�����AABB�Ƃ̍ŒZ�����̂Q����v�Z
	float distance = DistancePointToBox(data, max, min);

	// �������J�v�Z���̔��a�ȓ����ǂ����𔻒�
	return distance <= (data.Radius * data.Radius);
}

float StageCollisionManager::DistancePointToBox(CapsuleData data, Vec3 max, Vec3 min)
{
	// ���̒l�Ɣ�r���邽�߂ɍő�l�ŏ���������
	float minDist = FLT_MAX;

	// AABB���ɐ������܂܂�Ă��邩�`�F�b�N����
	Vec3 closetPointStart = ClosetPointBox(max, min, data.PointA);
	Vec3 closetPointEnd = ClosetPointBox(max, min, data.PointB);

	// �����̊J�n�_��AABB���ɂ���ꍇ
	if (closetPointStart.x == data.PointA.x &&
		closetPointStart.y == data.PointA.y &&
		closetPointStart.z == data.PointA.z) {
		return 0.0f;	// �����̓[��
	}

	// �����̏I���_��AABB�Ȃ��ɂ���ꍇ
	if (closetPointEnd.x == data.PointB.x &&
		closetPointEnd.y == data.PointB.y &&
		closetPointEnd.z == data.PointB.z) {
		return 0.0f;	// �����̓[��
	}

	// �����̊e�[�_����AABB�ւ̋������v�Z
	float distStart = (data.PointA - closetPointStart).SqLength();
	float distEnd = (data.PointB - closetPointEnd).SqLength();

	// �ŏ��̒l�����߂�
	minDist = (std::min)(distStart, distEnd);

	return minDist;
}

Vec3 StageCollisionManager::ClosetPointBox(Vec3 max, Vec3 min, Vec3 point)
{
	// �ŋߐړ_
	Vec3 closestPoint;

	// xyz���ɂ��Ĕ���
	closestPoint.x = (std::max)(min.x, (std::min)(point.x, max.x));
	closestPoint.y = (std::max)(min.y, (std::min)(point.y, max.y));
	closestPoint.z = (std::max)(min.z, (std::min)(point.z, max.z));
	//DrawSphere3D(closestPoint.VGet(), 2, 8, 0xffff00, 0xffff00, true);

	return closestPoint;
}

ColData StageCollisionManager::CreateMoveVector(Vec3 max, Vec3 min, CapsuleData data)
{
	// �����钼�O�ɃJ�v�Z�����{�b�N�X�ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
	// �{�b�N�X�̒��Œ��O�̃J�v�Z���̒��S�ɍł��߂��_���Z�o
	Vec3 closestA, closestB, unit;

	ColData colData;

	colData.max = max;
	colData.min = min;

	closestA = ClosetPointBox(max, min, data.FrontPointA);
	closestB = ClosetPointBox(max, min, data.FrontPointB);

	// ���߂��������߂�
	if ((closestA - data.FrontPointA).Length() < (closestB - data.FrontPointB).Length()) {

		// A�̂ق����߂�

		// �O�t���[����A��y���W���甼�a���������l��max��y����ɂ����y�̂݌v�Zy��艺��������xz�̂݌v�Z

		if (((data.FrontPointA.y - data.Radius) >= max.y)) {	// y�̂݌v�Z

			Vec3 target = Vec3{ data.PointA.x,max.y + data.Radius,data.PointA.z };

			unit = (target - closestA).GetNormalized();
			colData.dist = (target - closestA).Length();

			colData.moveVec = Vec3{ 0.0f,target.y - data.PointA.y,0.0f };

			return colData;

		}
		else {	// xz�̂݌v�Z

			// �����钼�O�Ƀv���C���[�����ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
			// �l�p�`�̒��Œ��O�̃v���C���[�̒��S�ɍł��߂��_���v�Z
			float closestX = (std::max)(min.x, (std::min)(data.FrontPointA.x, max.x));
			float closestY = (std::max)(min.z, (std::min)(data.FrontPointA.z, max.z));

			// �ŋߓ_����v���C���[�̒��S�֌������P�ʃx�N�g�����쐬����
			Vec3 center = (Vec3{ data.FrontPointA.x,0.0f,data.FrontPointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized();

			// �ŋߓ_����v���C���[�̍��W�ւ̋��������߂�
			float length = (Vec3{ data.PointA.x,0.0f,data.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

			colData.dist = length;

			// ���a����O���W�ւ̋������������l���߂荞�񂾕��̋����ɂȂ�
			length = data.Radius - length;

			colData.moveVec = center * length;

			// �ŋߓ_����{�b�N�X�̔���O�ւ̈ړ��x�N�g�����쐬
			return colData;



		}
	}
	else {

		// B�̂ق����߂�
		// �O�t���[����B��y���W�ɔ��a���������l��min��yy��艺�ɂ����y�̂݌v�Z


		if (((data.FrontPointB.y + data.Radius) <= min.y)) {	// y�̂݌v�Z

			Vec3 target = Vec3{ data.PointB.x,min.y - data.Radius,data.PointB.z };

			unit = (target - closestB).GetNormalized();
			colData.dist = (target - closestB).Length();

			colData.moveVec = Vec3{ 0.0f,target.y + data.PointA.y,0.0f };

			return colData;

		}
		else {	// xz�̂݌v�Z

			// �����钼�O�Ƀv���C���[�����ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
			// �l�p�`�̒��Œ��O�̃v���C���[�̒��S�ɍł��߂��_���v�Z
			float closestX = (std::max)(min.x, (std::min)(data.FrontPointA.x, max.x));
			float closestY = (std::max)(min.z, (std::min)(data.FrontPointA.z, max.z));

			// �ŋߓ_����v���C���[�̒��S�֌������P�ʃx�N�g�����쐬����
			Vec3 center = (Vec3{ data.FrontPointA.x,0.0f,data.FrontPointA.z } - Vec3{ closestX,0.0f,closestY }).GetNormalized();

			// �ŋߓ_����v���C���[�̍��W�ւ̋��������߂�
			float length = (Vec3{ data.PointA.x,0.0f,data.PointA.z } - Vec3{ closestX,0.0f,closestY }).Length();

			colData.dist = length;

			// ���a����O���W�ւ̋������������l���߂荞�񂾕��̋����ɂȂ�
			length = data.Radius - length;

			colData.moveVec = center * length;

			// �ŋߓ_����{�b�N�X�̔���O�ւ̈ړ��x�N�g�����쐬
			return colData;
		};

	}
}

#include "StageCollisionManager.h"
#include "StageManager.h"
#include <algorithm>

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
	// �ړ��x�N�g��������������
	_vResultMove = 0;
	_vAllColldata.clear();
	_vAllMove.clear();

	Vec3 max, min;// �ő���W,�ŏ����W

	// �J�v�Z���ƃX�e�[�W�̓����蔻������
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 2; b++) {
			for (int c = 0; c < 10; c++) {

				// �Ώۂ̃{�b�N�X�����݂����ꍇ�̂ݔ��肷��
				if (_pStage->GetStageInfo(a, b, c) != 0) {

					// �{�b�N�X�̍ő���W�ƍŏ����W�����߂�
					max = Vec3{ static_cast<float>(a * 10),static_cast<float>(b * 10),static_cast<float>(c * 10) };
					min = Vec3{ max - 10 };

					// �߂荞��ł��邩�ǂ������肷��
					if (CollisionBoxCapsule(max, min, data)) {

						// ���炷���̈ړ��x�N�g�����쐬
						ColData colData = CreateMoveVector(max, min, data);

						// �z��ɕۑ�
						_vAllColldata.push_back(colData);
					}
				}
			}
		}
	}

	// dist���Z�����ɕ��בւ���
	std::sort(_vAllColldata.begin(), _vAllColldata.end(), CompareByDist);

	// dist���Z�����ɔ��肵�Ȃ��炸�炵�Ă���
	for (const auto& colData : _vAllColldata) {
		if (CollisionBoxCapsule(colData.max, colData.min, data)) {

			// �ړ��x�N�g�����v�b�V������
			_vAllMove.push_back(colData.moveVec);
			
			// �J�v�Z���̃f�[�^�����W�ړ������Ă���
			data.PointA += colData.moveVec;
			data.PointB += colData.moveVec;
		}
	}

	// �ۑ������S�Ă̈ړ��x�N�g���𑫂��čŏI�I�Ȉړ��x�N�g�����쐬����
	for (auto vec : _vAllMove) {
		_vResultMove += vec;
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
	DrawSphere3D(closestPoint.VGet(), 2, 8, 0xffff00, 0xffff00, true);

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

		// A�̂ق����߂��ꍇ
		// �ŋߐړ_����A�܂ł̒P�ʃx�N�g�����쐬
		unit = (data.FrontPointA - closestA).GetNormalized();
		colData.dist = (closestA - data.PointA).Length();
	}
	else {

		// B�̂ق����߂��ꍇ
		// �ŋߐړ_����B�܂ł̒P�ʃx�N�g�����쐬
		unit = (data.FrontPointB - closestB).GetNormalized();
		colData.dist = (closestB - data.PointB).Length();
	}

	// �������Ă���ʂ𔻒肵�ĖʂƐ��������ȊO�̈ړ��ʂ��[���ɂ���
	// ���S�����ɃX���C�h���Ă��܂��o�O���N�����Ă��܂������߂̓ˊэH��
	if (std::abs(unit.x) > std::abs(unit.y) && std::abs(unit.x) > std::abs(unit.z)) {
		unit.y = 0;
		unit.z = 0;
	}
	else if (std::abs(unit.y) > std::abs(unit.x) && std::abs(unit.y) > std::abs(unit.z)) {
		unit.x = 0;
		unit.z = 0;
	}
	else {
		unit.x = 0;
		unit.y = 0;
	}

	// ���a����O���W�ւ̋������������l���߂荞�񂾕��̋����ɂȂ�

	colData.moveVec = (unit * (data.Radius - colData.dist));


	return colData;
}

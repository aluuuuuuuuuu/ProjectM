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

Vec3 StageCollisionManager::CapsuleCollision(CapsuleData data)
{
	// �ړ��x�N�g��������������
	_vResultMove = 0;
	_vAllMove.clear();

	Vec3 max;	// �ő咸�_
	Vec3 min;	// �Œᒸ�_

	// �J�v�Z���ƃX�e�[�W�̓����蔻������
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 2; b++) {
			for (int c = 0; c < 10; c++) {

				// �Ώۂ̃{�b�N�X�����݂����ꍇ�̂ݔ��肷��
				if (_pStage->GetStageInfo(a, b, c) != 0) {
					// �{�b�N�X�̍ő咸�_�����߂�
					max = Vec3{ static_cast<float>(a * 10),static_cast<float>(b * 10),static_cast<float>(c * 10) };

					// �{�b�N�X�̍Œᒸ�_�����߂�
					min = Vec3{ max - 10 };

					// ���肷��
					if (CollisionBoxCapsule(max, min, data)) {
						DrawString(10, 10, "unko", 0xffffff);
						// �������Ă����ꍇ���炷���̈ړ��N�g�����쐬���ĕۑ�����
						_vAllMove.push_back(CreateMoveVector(max, min, data));
					}
				}
			}
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
	// �J�v�Z���̒��S�����̍ŋߐړ_�����߂�
	Vec3 lineDir = data.FrontPointB - data.FrontPointA;

	float lineLength = lineDir.SqLength();
	if (lineLength == 0.0f) {
		return DistancePointToBox(data.FrontPointA, max, min) <= data.Radius * data.Radius;
	}

	// �J�v�Z���̐����̍ŋߐړ_���{�b�N�X�ɑ΂��ăN�����v
	Vec3 pointOnLine;
	for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
		pointOnLine = data.FrontPointA + lineDir * t;
		if(DistancePointToBox(pointOnLine,max,min) <= data.Radius * data.Radius){
			return true;
		}
	}

	return false;
}

float StageCollisionManager::DistancePointToBox(Vec3 point, Vec3 max, Vec3 min)
{
	float dist = 0.0f;

	// �e���ɃN�����v���ē_���{�b�N�X�̊O�ɂ��邩���m�F����
	if (point.x < max.x) {
		dist += (min.x - point.x) * (min.x - point.x);
	}
	else if (point.x > max.x) {
		dist += (point.x - max.x) * (point.x - max.x);
	}

	if (point.y < max.y) {
		dist += (min.y - point.y) * (min.y - point.y);
	}
	else if (point.y > max.y) {
		dist += (point.y - max.y) * (point.y - max.y);
	}

	if (point.z < max.z) {
		dist += (min.z - point.z) * (min.z - point.z);
	}
	else if (point.z > max.z) {
		dist += (point.z - max.z) * (point.z - max.z);
	}

	return dist;
}

Vec3 StageCollisionManager::CreateMoveVector(Vec3 max, Vec3 min, CapsuleData data)
{
	// �����钼�O�ɃJ�v�Z�����{�b�N�X�ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
	// �{�b�N�X�̒��Œ��O�̃J�v�Z���̒��S�ɍł��߂��_���Z�o
	Vec3 closest;
	closest.x = (std::max)(min.x, (std::min)(data.FrontPointA.x, max.x));
	closest.y = (std::max)(min.y, (std::min)(data.FrontPointA.y, max.y));
	closest.z = (std::max)(min.z, (std::min)(data.FrontPointA.z, max.z));

	// �ŋߐړ_����O�t���[���̃J�v�Z���̒��S�֌������P�ʃx�N�g�����쐬����
	//Vec3 unitVec = ()
	return Vec3();
}

#include "CollisionManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Components.h"

CollisionManager::CollisionManager(std::shared_ptr <StageManager>& stage) :
	_pStage(stage)
{
}

CollisionManager::~CollisionManager()
{
}

ColResult CollisionManager::PlayerCollision(std::vector<std::shared_ptr<Player>>& player)
{
	ColResult result;

	for (int i = 0; i < player.size(); i++) {
		// �ړ��x�N�g��������������
		_vResultMove = 0;

		// �J�v�Z���ƃJ�v�Z���̓����蔻����Ƃ�

		float moveDist = (player[i]->_data.FrontPointA - player[i]->_data.PointA).Length();

		for (int n = 0; n < player.size(); n++) {

			// �v���C���[�����g�Ɠ����蔻����Ƃ�Ȃ��悤�ɂ���
			if (n != i) {
				// �J�v�Z���̐������m�̋��������߂�
				float dist = DistanceLineToLine(player[i]->_data, player[n]->_data);

				// ��̃J�v�Z���̔��a�𑫂����l��苗�����Z����Γ������Ă���
				if (dist <= player[i]->_data.Radius + player[n]->_data.Radius) {

					if (moveDist >= (player[n]->_data.FrontPointA - player[n]->_data.PointA).Length()) {

						if (player[n]->GetGroundFlag()) {
							float aaaa = (player[n]->_data.FrontPointA - player[n]->_data.PointA).Length();
							Vec3 vec = CreateMoveVectorCapsule(player[i]->_data, player[n]->_data, dist);
							_vResultMove += vec;

							player[i]->_data.PointA += vec;
							player[i]->_data.PointB += vec;
						}
					}
				}
			}
		}

		// �J�v�Z���ƃX�e�[�W�̓����蔻������

		Vec3 max, min;// �ő���W,�ŏ����W

		for (int a = 0; a < BLOCK_NUM_X; a++) {
			for (int b = 0; b < BLOCK_NUM_Y; b++) {
				for (int c = 0; c < BLOCK_NUM_Z; c++) {

					// �Ώۂ̃{�b�N�X�����݂����ꍇ�̂ݔ��肷��
					if (_pStage->GetStageInfo(a, b, c) != 0) {

						// �{�b�N�X�̍ő���W�ƍŏ����W�����߂�
						Vec3 vec = { a,b,c };
						max = Vec3{ vec * _pStage->GetConstantInt("BLOCK_SIZE") };
						min = Vec3{ max - _pStage->GetConstantInt("BLOCK_SIZE") };

						// �߂荞��ł��邩�ǂ������肷��
						if (CollisionBoxCapsule(max, min, player[i]->_data)) {

							// ���炷���̈ړ��x�N�g�����쐬
							Vec3 vec = CreateMoveVectorBox(max, min, player[i]->_data);

							// �z��ɕۑ�
							_vResultMove += vec;

							player[i]->_data.PointA += vec;
							player[i]->_data.PointB += vec;
						}
					}
				}
			}
		}
		// �ŏI�I�Ȉړ��x�N�g����Ԃ�
		result.vec[i] = _vResultMove;
	}

	return result;
}

bool CollisionManager::CollisionBoxCapsule(Vec3 max, Vec3 min, CapsuleData data)
{
	// �J�v�Z���̐�����AABB�Ƃ̍ŒZ�����̂Q����v�Z
	float distance = DistancePointToBox(data, max, min);

	// �������J�v�Z���̔��a�ȓ����ǂ����𔻒�
	return distance <= (data.Radius * data.Radius);
}

float CollisionManager::DistancePointToBox(CapsuleData data, Vec3 max, Vec3 min)
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

Vec3 CollisionManager::ClosetPointBox(Vec3 max, Vec3 min, Vec3 point)
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

Vec3 CollisionManager::CreateMoveVectorBox(Vec3 max, Vec3 min, CapsuleData data)
{
	// �����钼�O�ɃJ�v�Z�����{�b�N�X�ɑ΂��Ăǂ̈ʒu�ɂ����̂��𒲂ׂ�
	// �{�b�N�X�̒��Œ��O�̃J�v�Z���̒��S�ɍł��߂��_���Z�o
	Vec3 closestA, closestB, unit;

	ColDataT colData;

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

			return colData.moveVec;

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
			return colData.moveVec;



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

			return colData.moveVec;

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
			return colData.moveVec;
		};

	}
}

float CollisionManager::DistanceLineToLine(CapsuleData dataA, CapsuleData dataB)
{
	Vec3 d1 = dataA.PointA - dataA.PointB;
	Vec3 d2 = dataB.PointA - dataB.PointB;
	Vec3 r = dataA.PointA - dataB.PointA;
	float a = d1.dot(d1);
	float e = d2.dot(d2);
	float f = d2.dot(r);

	float s, t;
	const float epsilon = static_cast<float>(1e-6);
	float c = d1.dot(r);
	float b = d1.dot(d2);
	float denom = a * e - b * b;

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

	Vec3 closestPoint1 = dataA.PointA + d1 * s;
	Vec3 closestPoint2 = dataB.PointA + d2 * t;
	return (closestPoint1 - closestPoint2).Length();
}

Vec3 CollisionManager::CreateMoveVectorCapsule(CapsuleData dataA, CapsuleData dataB, float dist)
{
	// ���̍��W����O�̍��W�܂ł̒P�ʃx�N�g�������߂�
	//Vec3 unit = (Vec3{ dataA.FrontPointA.x,0.0f,dataA.FrontPointA.z } - Vec3{ dataA.PointA.x,0.0f, dataA.PointA.z }).GetNormalized();
	Vec3 unit = (dataA.FrontPointA - dataB.PointA).GetNormalized();

	// �߂荞��ł��镪�̋��������߂�
	float full = dataA.Radius + dataB.Radius;
	float cave = full - dist;

	// �ړ��x�N�g�������߂�
	return unit * cave;
}

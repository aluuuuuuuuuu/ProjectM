#include "MapBulletCollisionManager.h"
#include "StageManager.h"
#include "Vec3.h"
#include "BulletManager.h"
#include "DxLib.h"

MapBulletCollisionManager::MapBulletCollisionManager(std::shared_ptr<StageManager>& stage) :
	_stage(stage)
{
}

MapBulletCollisionManager::~MapBulletCollisionManager()
{
}

bool MapBulletCollisionManager::CollisionBullet(Vec3 pos, float radius, int bullet)
{
	Vec3 max, min;// �ő���W,�ŏ����W
	// �J�v�Z���ƃX�e�[�W�̓����蔻������
	for (int a = 0; a < BLOCK_NUM_X; a++) {
		for (int b = 0; b < BLOCK_NUM_Y; b++) {
			for (int c = 0; c < BLOCK_NUM_Z; c++) {

				// �Ώۂ̃{�b�N�X�����݂����ꍇ�̂ݔ��肷��
				if (_stage->GetStageInfo(a, b, c) != 0) {

					// �{�b�N�X�̍ő���W�ƍŏ����W�����߂�
					max = Vec3{ static_cast<float>(a * 10),static_cast<float>(b * 10),static_cast<float>(c * 10) };
					min = Vec3{ max - 10 };

					// �߂荞��ł��邩�ǂ������肷��
					if (CollisionSphire(max, min, pos, radius)) {

						// �e���Ƃ̏������s��
						switch (bullet)
						{
						case NORMAL_BULLET:
							// ���������}�X���폜����
							_stage->DeleteBox(a, b, c);
							break;
						case GRAPPLER_BULLET:
							// �}�b�v�ɂ͉e����^���Ȃ�
							break;
						case BOMB_BULLET:
							// ���������}�X�̎��͂��폜����
							_stage->DeleteBox(a, b, c);
							_stage->DeleteBox(a, b - 1, c);

							_stage->DeleteBox(a - 1, b, c);
							_stage->DeleteBox(a + 1, b, c);
							_stage->DeleteBox(a, b, c + 1);
							_stage->DeleteBox(a, b, c - 1);

							break;
						default:
							break;
						}

						// ���������ƕԂ�
						return true;

					}
				}
			}
		}
	}

	return false;
}

bool MapBulletCollisionManager::CollisionSphire(Vec3 max, Vec3 min, Vec3 pos, float radius)
{
	// �J�v�Z���̍��W��AABB�Ƃ̍ŒZ������2����v�Z
	float distance = DistancePointToBox(max, min, pos, radius);

	// �������J�v�Z���̔��a�ȓ����ǂ����𔻒�
	return distance <= radius;
}

float MapBulletCollisionManager::DistancePointToBox(Vec3 max, Vec3 min, Vec3 pos, float radius)
{
	// AABB�ɐ������܂܂�Ă��邩�`�F�b�N����
	Vec3 closestPoint = ClosestPointBox(max, min, pos);

	// ���W��AABB���ɂ���ꍇ
	if (closestPoint.x == pos.x &&
		closestPoint.y == pos.y &&
		closestPoint.z == pos.z) {
		return 0.0f;	// �����̓[��
	}

	// ���W����AABB�ւ̋������v�Z
	float dist = (pos - closestPoint).SqLength();

	return dist;
}

Vec3 MapBulletCollisionManager::ClosestPointBox(Vec3 max, Vec3 min, Vec3 pos)
{
	// �ŋߐړ_
	Vec3 closestPoint;

	// xyz���ɂ��Ĕ���
	closestPoint.x = (std::max)(min.x, (std::min)(pos.x, max.x));
	closestPoint.y = (std::max)(min.y, (std::min)(pos.y, max.y));
	closestPoint.z = (std::max)(min.z, (std::min)(pos.z, max.z));

	return closestPoint;
}

#pragma once
#include <memory>
#include "Vec3.h"
#include "Components.h"
#include <vector>

struct ColDataT
{
	Vec3 max = 0;
	Vec3 min = 0;
	Vec3 moveVec = 0;
	float dist = 0;
};

struct ColResult
{
	Vec3 vec[4];
};

class Player;
class StageManager;
class CollisionManager
{
public:
	CollisionManager(std::shared_ptr <StageManager>& stage);
	~CollisionManager();

	ColResult PlayerCollision(std::vector<std::shared_ptr<Player>>& player);
private:

	/// <summary>
	/// �{�b�N�X�ƃJ�v�Z���̓����蔻������
	/// </summary>
	/// <param name="max">�{�b�N�X�̍ő���W</param>
	/// <param name="min">�{�b�N�X�̍ŏ����W</param>
	/// <param name ="data">�J�v�Z���̃f�[�^</param>
	/// <returns>�������Ă����true</returns>
	bool CollisionBoxCapsule(Vec3 max, Vec3 min, CapsuleData data);
	
	/// <summary>
	/// �_�ƃ{�b�N�X�̍ŒZ���������߂�
	/// </summary>
	/// <param name="point">�_�̍��W</param>
	/// <param name="max">�{�b�N�X�̍ő���W</param>
	/// <param name="min">�{�b�N�X�̍ŏ����W</param>
	/// <returns></returns>
	float DistancePointToBox(CapsuleData data, Vec3 max, Vec3 min);

	/// <summary>
	/// BOX��̍ŋߐړ_�����߂�֐�
	/// </summary>
	/// <param name="max">�ő���W</param>
	/// <param name="min">�ŏ����W</param>
	/// <param name="point">��r������W</param>
	/// <returns>�ŋߐړ_</returns>
	Vec3 ClosetPointBox(Vec3 max, Vec3 min, Vec3 point);

	/// <summary>
	/// �{�b�N�X�ɂ߂荞�񂾕��̃J�v�Z�������炷�ړ��x�N�g�����쐬����
	/// </summary>
	/// <param name="max">�{�b�N�X�̍ő���W</param>
	/// <param name="min">�{�b�N�X�̍ŏ����W</param>
	/// <param name="data">�J�v�Z���̃f�[�^</param>
	/// <returns>���炷���̈ړ��x�N�g��</returns>
	Vec3 CreateMoveVectorBox(Vec3 max, Vec3 min, CapsuleData data);

	/// <summary>
	/// �������m�̋��������߂�
	/// </summary>
	/// <param name="dataA">�����蔻��p�f�[�^A</param>
	/// <param name="dataB">�����蔻��p�f�[�^B</param>
	/// <returns>����</returns>
	float DistanceLineToLine(CapsuleData dataA, CapsuleData dataB);

	Vec3 CreateMoveVectorCapsule(CapsuleData dataA, CapsuleData dataB, float dist);

	// �ŏI�I�ɂ��炷�ړ��x�N�g��
	Vec3 _vResultMove;

	// �X�e�[�W�}�l�[�W���[�̎Q��
	std::shared_ptr<StageManager>& _pStage;
};


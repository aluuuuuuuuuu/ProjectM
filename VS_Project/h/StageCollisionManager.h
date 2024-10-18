#pragma once
#include <memory>
#include "Vec3.h"
#include "Components.h"

struct ColData
{
	Vec3 max = 0;
	Vec3 min = 0;
	Vec3 moveVec = 0;
	float dist = 0;
};

class StageManager;
class StageCollisionManager
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageCollisionManager(std::shared_ptr <StageManager>& stage);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~StageCollisionManager();

	
	/// <summary>
	/// �J�v�Z���ƃX�e�[�W�̓����蔻������
	/// </summary>
	/// <param name="data">�����蔻������Ώۂ̃J�v�Z���f�[�^</param>
	/// <returns>���肵�����ʂ��炷�ړ��x�N�g��</returns>
	Vec3 CapsuleCollision(CapsuleData data);

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
	ColData CreateMoveVector(Vec3 max, Vec3 min, CapsuleData data);

	// �ŏI�I�ɂ��炷�ړ��x�N�g��
	Vec3 _vResultMove;

	// ���肵���f�[�^
	std::vector<ColData> _vAllColldata;

	// �ړ��x�N�g��
	std::vector<Vec3> _vAllMove;

	// �X�e�[�W�}�l�[�W���[�̎Q��
	std::shared_ptr<StageManager>& _pStage;


	bool testFlag = false;
};


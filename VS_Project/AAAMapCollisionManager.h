#pragma once
#include "Components.h"
#include "Constant.h"
#include <vector>
#include <memory>


class StaticObjectManager;
class MapCollisionManager:
	public Constant
{
public:
	MapCollisionManager(CapsuleData& cap,StaticObjectManager& manager);
	virtual ~MapCollisionManager();

	// �v���C���[�ƐÓI�I�u�W�F�N�g�̓����蔻����Ƃ��Ĉړ�����x�N�g����Ԃ�
	Vec3 PlayerCollision();

	// �}�b�v�̓�������̃e�X�g�\��
	void DrawColl();

	// ���i�̕`��
	void DrawBoxColl(Vec3 min, Vec3 max);

private:

	// �J�v�Z���ƃ{�b�N�X�̕��ʏ�̓����蔻����Ƃ�֐�
	bool ColliosionBoxCapsuleParallel(Vec3 min, Vec3 max);

	// �v���C���[�������ړ��x�N�g����Ԃ�
	Vec3 CollisionMove(Vec3 min, Vec3 max);

	// �v���C���[�̃J�v�Z���̏��
	CapsuleData& m_playerCapsule;

	// �ÓI�I�u�W�F�N�g�}�l�[�W���[�̎Q��
	StaticObjectManager& m_staticObjectManager;

	// �v���C���[�̑O�t���[���̍��W
	CapsuleData m_beforePlayerPos;

	// �Փ˂��Ă��邷�ׂĂ̕ǂ̈ړ��x�N�g��
	std::vector<Vec3> m_move;

	// �ŏI�I�ȕǂɑ΂���R���W�����̈ړ��x�N�g��
	Vec3 m_lastMoveVec;
};


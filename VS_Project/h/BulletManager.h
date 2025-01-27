#pragma once
#include "BulletBase.h"
#include <memory>
#include <list>
#include <Constant.h>

#define NORMAL_BULLET 0
#define GRAPPLER_BULLET 1
#define BOMB_BULLET 2

#define MAX_TYPE_NUM 3
#define MIN_TYPE_NUM 0

class WedgewormManager;
class MapBulletCollisionManager;
class BulletBase;
class BulletManager :
	public Constant
{
public:
	BulletManager(std::shared_ptr<MapBulletCollisionManager>& col, std::shared_ptr<WedgewormManager>& worm);
	virtual ~BulletManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �v���C���[���ĂԊ֐��A�w��̒e�𔭎˂���
	/// </summary>
	/// <param name="bul">�e�̎��</param>
	/// <param name="dist">�����x�N�g��</param>
	/// <param name="pos">���W</param>
	/// <param name="plNum">�v���C���[�i���o�[</param>
	void PushBullet(int bul, Vec3 dist, Vec3 pos, int plnum);
	
	/// <summary>
	/// ����O���b�v���[�������������ǂ�����Ԃ��֐�
	/// </summary>
	/// <param name="plNum">�v���C���[�i���o�[<</param>
	/// <returns>�������Ă�����true</returns>
	bool IsCollisionBullet(int plNum);

	/// <summary>
	/// �e������������Ă��邩�Ԃ�����O���b�v���[�̂�
	/// </summary>
	/// <param name="plNum">�v���C���[�i���o�[<</param>
	/// <returns>�����ł����true</returns>
	bool GetInvalidFlag(int plNum) const;

	/// <summary>
	/// �e�𖳌������錻��O���b�v���[�̂�
	/// </summary>
	/// <param name="plNum">�v���C���[�i���o�[<</param>
	void KillBullet(int plNum);

	
	/// <summary>
	/// ����O���b�v���[�݂̂̍��W��Ԃ�
	/// </summary>
	/// <param name="plNum">�v���C���[�i���o�[<</param>
	/// <returns>�e�̍��W</returns>
	Vec3 GetBulletPos(int plNum);

	/// <summary>
	/// ����O���b�v���[�����݂��Ă��邩�ǂ����Ԃ�
	/// </summary>
	/// <param name="plNum">�v���C���[�i���o�[</param>
	/// <returns>���݂��Ă�����true</returns>
	bool GetBulletExist(int plNum);

private:

	// �o���b�g��ۑ����郊�X�g�z��
	std::list<std::shared_ptr<BulletBase>> _pBullet;

	// �R���W�����}�l�[�W���[�̎Q��
	std::shared_ptr<MapBulletCollisionManager>& _collManager;

	// �S���}�l�[�W���[�̎Q��
	std::shared_ptr<WedgewormManager>& _wedgeManager;
};

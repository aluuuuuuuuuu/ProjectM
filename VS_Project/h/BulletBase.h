#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include "Components.h"
#include <memory>

class MyEffect;
class BulletManager;
class MapBulletCollisionManager;
class BulletBase:
	public Transform
{
public:
	BulletBase();
	virtual ~BulletBase() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// ���S�t���O��Ԃ�
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool IsDead() const;

	 /// <summary>
	 /// ���g�̒e�̎�ނ�Ԃ�
	 /// </summary>
	 /// <returns>�o���b�g�}�l�[�W���[�̒萔</returns>
	 int GetBulletType() const;

	 /// <summary>
	 /// �}�b�v�Ɠ����������ǂ�����Ԃ�����O���b�v���[�̂ݔ���
	 /// </summary>
	 /// <returns>�������Ă�����true</returns>
	 bool GetCollisionFlag() const;

	 /// <summary>
	 /// �e������������Ă��邩�Ԃ�����O���b�v���[�̂�
	 /// </summary>
	 /// <returns>�����ł����true</returns>
	 bool GetInvalidFlag() const;

	 /// <summary>
	 /// �e�𖳌�������
	 /// </summary>
	 void KillBullet();

	 /// <summary>
	 /// ���g���ǂ̃v���C���[���甭�˂��ꂽ����Ԃ�
	 /// </summary>
	 /// <returns>�v���C���[�i���o�[</returns>
	 int GetPlayerNum();

protected:

	// ���S�t���O
	bool _deadFlag;

	// ���g�̒e�̎��
	int _bulletType;

	// ���������t���O
	bool _collisionFlag;

	// �����t���O
	bool _invalidFlag;

	// ���g���ǂ̃v���C���[���甭�˂��ꂽ����ۑ����Ă���
	int _playerNum;

	// �ړ������x�N�g��
	Vec3 _distVec;

	// �d��
	float _gravity;

	// �G�t�F�N�g�|�C���^
	std::shared_ptr<MyEffect> _pEffect;

};


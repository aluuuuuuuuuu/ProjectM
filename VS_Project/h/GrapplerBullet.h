#pragma once
#include <memory>
#include "BulletBase.h"

class BulletManager;
class MapBulletCollisionManager;
class GrapplerBullet :
    public BulletBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="dist">�����x�N�g��</param>
    /// <param name="pos">����������W</param>
    /// <param name="col">�R���W�����}�l�[�W���[</param>
    /// <param name="mgr">�o���b�g�}�l�[�W���[</param>
    GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GrapplerBullet();

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() const;
private:

    // �ړ������x�N�g��
    Vec3 _distVec;

    // �d��
    float _gravity;

    // �R���W�����}�l�[�W���[�̎Q��
    std::shared_ptr<MapBulletCollisionManager>& _collManager;

    // �o���b�g�}�l�[�W���[�̎Q��
    BulletManager& _bulletManager;
};

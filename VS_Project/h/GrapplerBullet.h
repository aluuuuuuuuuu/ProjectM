#pragma once
#include <memory>
#include "BulletBase.h"

class WedgewormManager;
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
    /// <param name="plNum">�v���C���[�i���o�[</param>
    GrapplerBullet(Vec3 dist, Vec3 pos, std::shared_ptr<MapBulletCollisionManager>& col, BulletManager& mgr, int plNum, std::shared_ptr<WedgewormManager>& wedge);

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

     /// <summary>
     /// �S���Ɠ�����������Ԃ�
     /// </summary>
     /// <param name="plNum">�v���C���[�i���o�[</param>
     /// <returns>�������ĂȂ��������̓O���b�v���łȂ����false</returns>
    bool WedgeCollision(int plNum);
private:

    // �R���W�����}�l�[�W���[�̎Q��
    std::shared_ptr<MapBulletCollisionManager>& _collManager;

    // �o���b�g�}�l�[�W���[�̎Q��
    BulletManager& _bulletManager;

    // �S���}�l�[�W���[�̎Q��
    std::shared_ptr<WedgewormManager>& _wedgeManager;

    int _frame;
};


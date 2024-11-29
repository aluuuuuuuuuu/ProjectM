#pragma once
#include "SceneBase.h"
#include <memory>
#include "PlayerManager.h"

class NumUtility;
class ResultUi;
class SceneResult :
    public SceneBase
{
public:

   
    SceneResult(PlayerData data);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneResult();

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() const;

private:
    // �������p�|�C���^
    std::shared_ptr<NumUtility> _pNum;

    // ���U���g���S�|�C���^
    std::shared_ptr<ResultUi> _pResultUi;

    // �v���C���[�f�[�^��ێ�����
    PlayerData _playerData;

    int test;
};


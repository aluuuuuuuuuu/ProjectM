#pragma once
#include "SceneBase.h"
#include <memory>
#include "PlayerManager.h"

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

    PlayerData _playerData;
};


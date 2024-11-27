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
    /// デストラクタ
    /// </summary>
    virtual ~SceneResult();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() const;

private:

    PlayerData _playerData;
};


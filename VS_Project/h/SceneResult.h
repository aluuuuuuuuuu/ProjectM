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
    // 数字利用ポインタ
    std::shared_ptr<NumUtility> _pNum;

    // リザルトロゴポインタ
    std::shared_ptr<ResultUi> _pResultUi;

    // プレイヤーデータを保持する
    PlayerData _playerData;

    int test;
};


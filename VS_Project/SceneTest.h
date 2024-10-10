#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>

class Player;
class Stage;
class SceneTest :
    public SceneBase,
    public Constant
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneTest();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneTest();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() const;

private:
    /// <summary>
    /// グリッド表示
    /// </summary>
    void DrawGrid() const;

    // 関数ポインタ
    using m_updateFunc_t = void (SceneTest::*)();
    using m_drawFunc_t = void (SceneTest::*)() const;
    m_updateFunc_t _updateFunc = nullptr;
    m_drawFunc_t _drawFunc = nullptr;

    /// <summary>
    /// 通常の更新処理
    /// </summary>
    void NormalUpdate();

    /// <summary>
    /// 通常の描画処理
    /// </summary>
    void NormalDraw() const;

    // ステージポインタ
    std::shared_ptr<Stage> _pStage;

    // プレイヤーポインタ
    std::shared_ptr<Player> _pPlayer;

};


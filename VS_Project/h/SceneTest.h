#pragma once
#include "SceneBase.h"
#include <memory>

class EnemyManager;
class MapCollisionManager;
class StaticObjectManager;
class Direction;
class Player;
// テストシーン
class SceneTest :
    public SceneBase
{
public:
    SceneTest();
    virtual ~SceneTest();

    void Update();
    void Draw() const;

    void DrawGrid() const;
private:

    // 関数ポインタ
    using m_updateFunc_t = void (SceneTest::*)();
    using m_drawFunc_t = void (SceneTest::*)() const;
    m_updateFunc_t m_updateFunc = nullptr;
    m_drawFunc_t m_drawFunc = nullptr;

    // 通常の処理
    void NormalUpdate();
    void NormalDraw() const;

    // シーケンス中の処理
    void SeqUpdate();
    void SeqDraw() const;

    // プレイヤーのポインタ
    std::shared_ptr<Player> m_pPlayer;

    // ディレクションのぽインタ
    std::shared_ptr<Direction> m_pDirection;

    // スタティックオブジェクトマネージャーのポインタ
    std::shared_ptr<StaticObjectManager> m_pStaticObject;

    // コリジョンマネージャーのポインタ
    std::shared_ptr<MapCollisionManager> m_pCollisionManager;

    // エネミーマネージャーのポインタ
    std::shared_ptr<EnemyManager> m_pEnemyManager;
};


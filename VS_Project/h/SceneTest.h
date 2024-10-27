#pragma once
#include "SceneBase.h"
#include "Constant.h"
#include <memory>
#include <vector>

struct VECTOR4
{
    int a;
    int b;
    int c;
    int d;
};

struct VECTOR2
{
    int a;
    int b;
};

class MapBulletCollisionManager;
class BulletManager;
class StageCollisionManager;
class Player;
class StageManager;
class SceneTest :
    public SceneBase,
    public Constant
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="playerNum">プレイヤーの数</param>
    SceneTest(int playerNum);

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

    /// <summary>
    /// プレイヤー数から描画範囲を求める
    /// </summary>
    /// <param name="num">プレイヤーの数-1/param>
    /// <param name="scWidth">スクリーンの幅</param>
    /// <param name="scHeight">スクリーンの高さ</param>
    /// <returns>描画範囲</returns>
    VECTOR4 CreateDrawArea(int num, int scWidth, int scHeight);
    
    /// <summary>
    /// プレイヤー数からスクリーンの中心を求める
    /// </summary>
    /// <param name="num">プレイヤーの数-1</param>
    /// <param name="scWidth">スクリーンの幅</param>
    /// <param name="scHeight">スクリーンの高さ</param>
    /// <returns>カメラの中心</returns>
    VECTOR2 CreateScreenCenter(int num, int scWidth, int scHeight);

    // ステージポインタ
    std::shared_ptr<StageManager> _pStage;

    // プレイヤーポインタ
    std::vector<std::shared_ptr<Player>> _pPlayer;

    // ステージコリジョンマネージャポインタ
    std::shared_ptr<StageCollisionManager> _pStageCollisionManager;

    // バレットマネージャポインタ
    std::shared_ptr<BulletManager> _pBulletManager;

    // バレットコリジョンマネージャー
    std::shared_ptr<MapBulletCollisionManager> _pBulletCollsionManager;

    int _windowWidth;
    int _windowHeight;

    VECTOR4 _drawArea[4];
    VECTOR2 _cameraSenter[4];

};


#pragma once
#include "ItemBase.h"

class StageManager;
class ItemSpeedUp :
    public ItemBase
{
public:

    ItemSpeedUp(Vec3 pos, std::shared_ptr<StageManager>& stageManager);

    ~ItemSpeedUp();

    void Update();

    void Draw() const;

private:
    std::shared_ptr<StageManager>& _pStage;
};


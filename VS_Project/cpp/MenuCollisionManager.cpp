#include "MenuCollisionManager.h"
#include "MenuManager.h"
#include "SelectFinger.h"

MenuCollisionManager::MenuCollisionManager(MenuManager& mane):
    _manager(mane)
{
}

MenuCollisionManager::~MenuCollisionManager()
{
}

int MenuCollisionManager::Collision(Vec2 fingPos)
{
    int judge = -1;
    // ���ׂẴ{�^���Ɣ�����Ƃ�
    for (int i = 0; i < ALL_BUTTON_NUM; i++) {

        // �������ĂȂ��ꍇ�����ׂď���
        if (_manager.GetPos(i).x - _manager.GetRange(i).x > fingPos.x) {
            continue;
        }
        if (_manager.GetPos(i).x + _manager.GetRange(i).x < fingPos.x) {
            continue;
        }
        if (_manager.GetPos(i).y - _manager.GetRange(i).y > fingPos.y) {
            continue;
        }
        if (_manager.GetPos(i).y + _manager.GetRange(i).y < fingPos.y) {
            continue;
        }

        // �������Ă����瓖�������{�^���̒萔��Ԃ�
        judge = i;
    }
    return judge;
}

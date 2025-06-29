#include "DrawPlayCards.h"

USING_NS_CC;
using namespace DrawLayout;

/**
 * @brief 创建主牌区背景图层。
 *
 * 该区域显示桌面上的可匹配卡牌。背景颜色为棕色系，放置在屏幕上方区域。
 *
 * @param width 图层宽度，通常为设计宽度。
 * @param height 图层高度，取 kMainAreaHeight。
 * @param origin 屏幕左下角原点坐标。
 * @return LayerColor* 创建好的主牌区背景层。
 */
LayerColor* DrawPlayCards::createMainArea(float width, float height, Vec2 origin) {
    auto backgroundLayer = LayerColor::create(Color4B(180, 120, 60, 255), width, height);
    backgroundLayer->setPosition(origin.x, origin.y + kDeckAreaHeight);  // 主区在堆区之上
    return backgroundLayer;
}

/**
 * @brief 创建堆牌区背景图层。
 *
 * 显示玩家的堆牌（如翻牌堆）。背景为紫色，靠近屏幕底部。
 *
 * @param width 图层宽度，通常为设计宽度。
 * @param height 图层高度，取 kDeckAreaHeight。
 * @param origin 屏幕左下角原点坐标。
 * @return LayerColor* 创建好的堆牌区背景层。
 */
LayerColor* DrawPlayCards::createDeckArea(float width, float height, Vec2 origin) {
    auto backgroundLayer = LayerColor::create(Color4B(128, 0, 128, 255), width, height);
    backgroundLayer->setPosition(origin.x, origin.y);  // 位于屏幕底部
    return backgroundLayer;
}

/**
 * @brief 创建“Undo”操作按钮菜单。
 *
 * 用于绑定回退操作，点击后调用传入的回调函数。
 *
 * @param callback 按钮点击回调函数。
 * @param position 按钮在屏幕上的位置。
 * @return Menu* 包含按钮的菜单实例，可直接加入场景中。
 */
Menu* DrawPlayCards::createUndoMenu(const std::function<void(Ref*)>& callback, Vec2 position) {
    auto undoLabel = Label::createWithSystemFont("Undo", "Arial", 36);
    auto undoItem = MenuItemLabel::create(undoLabel, callback);
    undoItem->setPosition(position);

    auto undoMenu = Menu::create(undoItem, nullptr);
    undoMenu->setPosition(Vec2::ZERO);  // 让菜单项相对坐标起作用
    return undoMenu;
}

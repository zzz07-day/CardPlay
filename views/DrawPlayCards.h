#pragma once
#ifndef __DRAW_PLAY_CARDS_H__
#define __DRAW_PLAY_CARDS_H__

#include "cocos2d.h"

/**
 * @namespace DrawLayout
 * @brief 定义视图层布局相关的常量。
 *
 * 包括设计宽高、主牌区与堆牌区的高度，用于控制界面布局。
 */
namespace DrawLayout {
    constexpr float kDesignWidth = 1080.0f;       ///< 游戏设计分辨率宽度
    constexpr float kDesignHeight = 2080.0f;      ///< 游戏设计分辨率高度
    constexpr float kMainAreaHeight = 1500.0f;    ///< 主牌区高度
    constexpr float kDeckAreaHeight = 580.0f;     ///< 堆牌区高度
}

/**
 * @class DrawPlayCards
 * @brief 视图绘制工具类，用于构建纸牌游戏界面中的背景区域和按钮菜单。
 *
 * 本类所有方法均为静态方法，负责将视图组件创建并返回给场景使用，提供背景区域的绘制和按钮功能。
 */
class DrawPlayCards {
public:
    /**
     * @brief 创建主牌区背景区域。
     * @param width 区域宽度（通常为设计宽度）。
     * @param height 区域高度（主牌区高度）。
     * @param origin 屏幕左下角原点坐标。
     * @return cocos2d::LayerColor* 创建的主牌区图层。
     */
    static cocos2d::LayerColor* createMainArea(float width, float height, cocos2d::Vec2 origin);

    /**
     * @brief 创建堆牌区背景区域。
     * @param width 区域宽度（通常为设计宽度）。
     * @param height 区域高度（堆牌区高度）。
     * @param origin 屏幕左下角原点坐标。
     * @return cocos2d::LayerColor* 创建的堆牌区图层。
     */
    static cocos2d::LayerColor* createDeckArea(float width, float height, cocos2d::Vec2 origin);

    /**
     * @brief 创建 Undo 按钮菜单。
     * @param callback 按钮点击后的回调函数。
     * @param position 菜单按钮的屏幕位置。
     * @return cocos2d::Menu* 包含按钮的菜单控件。
     */
    static cocos2d::Menu* createUndoMenu(const std::function<void(cocos2d::Ref*)>& callback, cocos2d::Vec2 position);
};

#endif // __DRAW_PLAY_CARDS_H__

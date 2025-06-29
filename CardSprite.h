#pragma once
#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum CardSuitType
 * @brief 表示卡牌的花色类型。
 *
 * - CST_CLUBS: 梅花
 * - CST_DIAMONDS: 方块
 * - CST_HEARTS: 红桃
 * - CST_SPADES: 黑桃
 */
enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      ///< 梅花
    CST_DIAMONDS,   ///< 方块
    CST_HEARTS,     ///< 红桃
    CST_SPADES,     ///< 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

/**
 * @enum CardFaceType
 * @brief 表示卡牌的点数类型。
 *
 * - CFT_ACE ~ CFT_KING: 分别对应 A ~ K
 */
enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,        ///< A (1)
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,       ///< K (13)
    CFT_NUM_CARD_FACE_TYPES
};

/**
 * @class CardSprite
 * @brief 表示一张可视化的卡牌节点，包含点数、花色、贴图等信息。
 *
 * 该类继承自 `cocos2d::Node`，用于构建卡牌的视觉组件，
 * 包括背景图、小字体、大字体与花色图标等。
 *
 * 使用场景：
 * - 游戏初始化阶段加载卡牌数据并展示在场景中。
 * - 提供点击事件、匹配判断、动画操作的实体对象。
 */
class CardSprite : public cocos2d::Node {

public:
    /**
     * @brief 创建一张卡牌精灵实例。
     * @param face 点数（1~13）
     * @param suit 花色（0~3）
     * @return 创建成功返回卡牌实例指针，否则返回 nullptr。
     */
    static CardSprite* create(int face, int suit);

    /**
     * @brief 初始化卡牌精灵。
     * @param face 点数
     * @param suit 花色
     * @return 初始化是否成功
     */
    virtual bool init(int face, int suit);

    /**
     * @brief 获取卡牌点数。
     * @return 返回卡牌点数（1~13）
     */
    int getCardFace() const { return _face; }

    /**
     * @brief 获取卡牌花色。
     * @return 返回卡牌花色（0~3）
     */
    int getCardSuit() const { return _suit; }

private:
    int _face;  ///< 卡牌点数（1~13）
    int _suit;  ///< 卡牌花色（0~3）

    cocos2d::Sprite* _bg;         ///< 卡牌背景精灵
    cocos2d::Sprite* _smallFace;  ///< 小字体精灵（左上角）
    cocos2d::Sprite* _bigFace;    ///< 大字体精灵（中央）
    cocos2d::Sprite* _suitIcon;   ///< 花色图标（右上角）

    /**
     * @brief 构建卡牌的可视元素，包括背景、小字体、大字体、花色图标等。
     */
    void buildCard();
};

#endif // __CARD_SPRITE_H__

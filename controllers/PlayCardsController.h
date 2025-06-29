#pragma once
#ifndef __PLAYCARDS_CONTROLLER_H__
#define __PLAYCARDS_CONTROLLER_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include <vector>

/**
 * @struct MoveRecord
 * @brief 表示一次移动操作的记录，用于支持回退机制。
 *
 * 包含操作卡牌的位置、所属节点以及之前的顶牌状态。
 */
struct MoveRecord {
    CardSprite* card;                  ///< 被移动的卡牌
    cocos2d::Vec2 fromPos;             ///< 原始位置（用于动画回退）
    cocos2d::Node* fromParent;         ///< 原始父节点（决定回退时回哪一层）
    CardSprite* prevTopCard;           ///< 移动之前的顶牌卡牌（用于回退时恢复）
};

/**
 * @class PlayCardsController
 * @brief 控制器类，负责纸牌游戏中的交互事件绑定与操作逻辑处理。
 *
 * 本类采用静态方法封装核心控制逻辑：
 * - 主牌区点击匹配逻辑；
 * - 堆牌区点击翻牌逻辑；
 * - 回退操作逻辑。
 *
 * 使用方式：由 PlayCards 场景调用各静态方法，进行事件绑定。
 */
class PlayCardsController {
public:
    /**
     * @brief 为主牌区卡牌绑定点击事件，实现点数匹配与替换逻辑。
     *
     * 匹配逻辑：判断所点击的主牌是否与顶部卡牌点数相差1，如果满足，则移动到顶部并更新状态。
     *
     * @param parent 当前场景或主区域节点。
     * @param _playfieldCards 主牌区中的所有卡牌。
     * @param _handStack 堆牌区中的卡牌栈。
     * @param _topCard 当前顶部卡牌，用于匹配判断。
     * @param _undoStack 操作记录栈，用于支持回退。
     */
    static void bindPlayfieldEvents(cocos2d::Node* parent,
        const std::vector<CardSprite*>& _playfieldCards,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard,
        std::vector<MoveRecord>& _undoStack);

    /**
     * @brief 为堆牌区绑定点击事件，实现翻牌到顶部逻辑。
     *
     * 玩家点击堆牌时，将所选卡牌移动为新的顶部卡牌，并记录操作。
     *
     * @param parent 当前场景或区域节点。
     * @param _handStack 堆牌区卡牌栈。
     * @param _topCard 当前顶部卡牌引用。
     * @param _undoStack 操作记录栈。
     */
    static void bindStackEvents(cocos2d::Node* parent,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard,
        std::vector<MoveRecord>& _undoStack);

    /**
     * @brief 执行回退操作，将最近一次卡牌移动还原。
     *
     * 回退内容包括：卡牌位置、所属层级恢复；顶部卡牌回滚。
     *
     * @param _undoStack 存储的操作记录栈。
     * @param _topCard 当前顶部卡牌引用，会被替换回上一次状态。
     */
    static void undoLastMove(std::vector<MoveRecord>& _undoStack, CardSprite*& _topCard);
};

#endif // __PLAYCARDS_CONTROLLER_H__

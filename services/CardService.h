#pragma once
#ifndef __CARD_SERVICE_H__
#define __CARD_SERVICE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include <vector>

/**
 * @class CardService
 * @brief 服务层类，负责加载并解析关卡配置文件，构建卡牌对象。
 *
 * CardService 类封装了与卡牌数据加载相关的逻辑，
 * 负责从 JSON 文件中读取卡牌信息并初始化主牌区、堆牌区和初始顶牌对象。
 *
 * 使用场景：
 * - 游戏初始化阶段调用，用于加载关卡配置（如 level1.json）。
 * - 将模型数据与视图层分离，实现解耦。
 */
class CardService {
public:
    /**
     * @brief 从配置文件加载一关卡的卡牌数据。
     *
     * 该函数将解析指定 JSON 文件，并初始化主牌区卡牌、堆牌区卡牌以及顶部卡牌指针。
     *
     * @param filename JSON 配置文件路径（相对于资源目录，如 "config/level1.json"）。
     * @param _playfieldCards [out] 主牌区卡牌容器，函数会填充该数组。
     * @param _handStack [out] 堆牌区卡牌容器，函数会填充该数组。
     * @param _topCard [out] 初始堆牌区顶牌指针，会被设置为堆牌区的最后一张卡牌。
     *
     * @return true 加载成功，false 加载失败或格式错误。
     */
    static bool loadLevelData(const std::string& filename,
        std::vector<CardSprite*>& _playfieldCards,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard);
};

#endif // __CARD_SERVICE_H__

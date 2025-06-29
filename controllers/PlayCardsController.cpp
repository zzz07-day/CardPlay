#include "PlayCardsController.h"

USING_NS_CC;

/**
 * @brief 绑定主牌区卡牌的点击匹配事件。
 *
 * 点击主牌卡牌后，会检查其点数是否与当前顶牌相差1（或 A 与 K 特判）。
 * 如果匹配成功，则执行移动动画，将该卡牌设为新顶牌，并记录操作以支持回退。
 *
 * @param parent 事件监听附加的父节点（通常为主场景）。
 * @param _playfieldCards 主牌区的卡牌列表。
 * @param _handStack 玩家手牌栈。
 * @param _topCard 当前顶部卡牌（用于匹配）。
 * @param _undoStack 回退记录栈。
 */
void PlayCardsController::bindPlayfieldEvents(Node* parent,
    const std::vector<CardSprite*>& _playfieldCards,
    std::vector<CardSprite*>& _handStack,
    CardSprite*& _topCard,
    std::vector<MoveRecord>& _undoStack) {

    for (auto& card : _playfieldCards) {
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);

        touchListener->onTouchBegan = [=, &_topCard, &_undoStack](Touch* touch, Event* event) -> bool {
            Vec2 locationInNode = card->convertToNodeSpace(touch->getLocation());
            Size size = card->getContentSize();

            if (Rect(0, 0, size.width, size.height).containsPoint(locationInNode)) {
                if (!_topCard) return false;

                int face1 = card->getCardFace();
                int face2 = _topCard->getCardFace();

                // 匹配条件：点数差1，或 A 和 K 可互换
                bool isMatch = (std::abs(face1 - face2) == 1) ||
                    (face1 == 1 && face2 == 13) ||
                    (face1 == 13 && face2 == 1);

                if (isMatch) {
                    // 记录旧状态以便回退
                    Vec2 worldPos = _topCard->getParent()->convertToWorldSpace(_topCard->getPosition());
                    _undoStack.push_back(MoveRecord{ card, card->getPosition(), card->getParent(), _topCard });

                    // 卡牌移除并加入新层级
                    card->retain();
                    card->removeFromParentAndCleanup(false);
                    parent->addChild(card, 100 + _handStack.size());
                    card->release();

                    // 执行移动动画并更新顶牌
                    Vec2 localPos = parent->convertToNodeSpace(worldPos);
                    card->setPosition(card->getParent()->convertToNodeSpace(touch->getLocation()));
                    card->runAction(Sequence::create(
                        MoveTo::create(0.3f, localPos),
                        CallFunc::create([=, &_topCard]() {
                            if (_topCard) _topCard->setVisible(false);
                            _topCard = card;
                            }),
                        nullptr));
                    return true;
                }
            }
            return false;
            };

        parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, card);
    }
}

/**
 * @brief 绑定堆牌区的点击事件，支持点击卡堆翻新顶牌。
 *
 * 点击非顶层卡牌时，触发翻牌操作，将其移到顶部并记录状态。
 *
 * @param parent 当前场景或图层节点。
 * @param _handStack 玩家手牌栈。
 * @param _topCard 当前顶部卡牌引用。
 * @param _undoStack 回退记录栈。
 */
void PlayCardsController::bindStackEvents(Node* parent,
    std::vector<CardSprite*>& _handStack,
    CardSprite*& _topCard,
    std::vector<MoveRecord>& _undoStack) {

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [=, &_topCard, &_undoStack](Touch* touch, Event* event) -> bool {
        Vec2 touchLocation = touch->getLocation();

        // 从底部向上检查非顶层卡牌是否被点击
        for (int i = 0; i < _handStack.size() - 1; ++i) {
            CardSprite* card = _handStack[i];
            if (card->getBoundingBox().containsPoint(touchLocation)) {
                _undoStack.push_back(MoveRecord{ card, card->getPosition(), card->getParent(), _topCard });

                Vec2 toPos = _topCard->getPosition();
                card->runAction(Sequence::create(
                    MoveTo::create(0.3f, toPos),
                    CallFunc::create([=, &_topCard]() {
                        if (_topCard) _topCard->setVisible(false);
                        _topCard = card;
                        card->setLocalZOrder(100 + _handStack.size());
                        }),
                    nullptr));
                return true;
            }
        }
        return false;
        };

    parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, parent);
}

/**
 * @brief 回退最近一次移动操作。
 *
 * 会将卡牌移回原位，并恢复前一个顶牌状态。
 * 若没有操作记录，则不会执行任何操作。
 *
 * @param _undoStack 操作记录栈。
 * @param _topCard 当前顶部卡牌引用，会被恢复为之前状态。
 */
void PlayCardsController::undoLastMove(std::vector<MoveRecord>& _undoStack, CardSprite*& _topCard) {
    if (_undoStack.empty()) return;

    MoveRecord last = _undoStack.back();
    _undoStack.pop_back();

    last.card->stopAllActions();
    last.card->retain();
    last.card->removeFromParentAndCleanup(false);

    last.fromParent->addChild(last.card);
    last.card->setPosition(last.card->getParent()->convertToNodeSpace(last.card->getPosition()));

    last.card->runAction(MoveTo::create(0.3f, last.fromPos));
    last.card->release();

    if (_topCard) _topCard->setVisible(false);
    last.card->setVisible(true);
    _topCard = last.prevTopCard;

    if (_topCard) _topCard->setVisible(true);
}

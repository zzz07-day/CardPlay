#include "PlayCardsController.h"

USING_NS_CC;

/**
 * @brief �����������Ƶĵ��ƥ���¼���
 *
 * ������ƿ��ƺ󣬻���������Ƿ��뵱ǰ�������1���� A �� K ���У���
 * ���ƥ��ɹ�����ִ���ƶ����������ÿ�����Ϊ�¶��ƣ�����¼������֧�ֻ��ˡ�
 *
 * @param parent �¼��������ӵĸ��ڵ㣨ͨ��Ϊ����������
 * @param _playfieldCards �������Ŀ����б�
 * @param _handStack �������ջ��
 * @param _topCard ��ǰ�������ƣ�����ƥ�䣩��
 * @param _undoStack ���˼�¼ջ��
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

                // ƥ��������������1���� A �� K �ɻ���
                bool isMatch = (std::abs(face1 - face2) == 1) ||
                    (face1 == 1 && face2 == 13) ||
                    (face1 == 13 && face2 == 1);

                if (isMatch) {
                    // ��¼��״̬�Ա����
                    Vec2 worldPos = _topCard->getParent()->convertToWorldSpace(_topCard->getPosition());
                    _undoStack.push_back(MoveRecord{ card, card->getPosition(), card->getParent(), _topCard });

                    // �����Ƴ��������²㼶
                    card->retain();
                    card->removeFromParentAndCleanup(false);
                    parent->addChild(card, 100 + _handStack.size());
                    card->release();

                    // ִ���ƶ����������¶���
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
 * @brief �󶨶������ĵ���¼���֧�ֵ�����ѷ��¶��ơ�
 *
 * ����Ƕ��㿨��ʱ���������Ʋ����������Ƶ���������¼״̬��
 *
 * @param parent ��ǰ������ͼ��ڵ㡣
 * @param _handStack �������ջ��
 * @param _topCard ��ǰ�����������á�
 * @param _undoStack ���˼�¼ջ��
 */
void PlayCardsController::bindStackEvents(Node* parent,
    std::vector<CardSprite*>& _handStack,
    CardSprite*& _topCard,
    std::vector<MoveRecord>& _undoStack) {

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [=, &_topCard, &_undoStack](Touch* touch, Event* event) -> bool {
        Vec2 touchLocation = touch->getLocation();

        // �ӵײ����ϼ��Ƕ��㿨���Ƿ񱻵��
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
 * @brief �������һ���ƶ�������
 *
 * �Ὣ�����ƻ�ԭλ�����ָ�ǰһ������״̬��
 * ��û�в�����¼���򲻻�ִ���κβ�����
 *
 * @param _undoStack ������¼ջ��
 * @param _topCard ��ǰ�����������ã��ᱻ�ָ�Ϊ֮ǰ״̬��
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

#pragma once
#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum CardSuitType
 * @brief ��ʾ���ƵĻ�ɫ���͡�
 *
 * - CST_CLUBS: ÷��
 * - CST_DIAMONDS: ����
 * - CST_HEARTS: ����
 * - CST_SPADES: ����
 */
enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      ///< ÷��
    CST_DIAMONDS,   ///< ����
    CST_HEARTS,     ///< ����
    CST_SPADES,     ///< ����
    CST_NUM_CARD_SUIT_TYPES
};

/**
 * @enum CardFaceType
 * @brief ��ʾ���Ƶĵ������͡�
 *
 * - CFT_ACE ~ CFT_KING: �ֱ��Ӧ A ~ K
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
 * @brief ��ʾһ�ſ��ӻ��Ŀ��ƽڵ㣬������������ɫ����ͼ����Ϣ��
 *
 * ����̳��� `cocos2d::Node`�����ڹ������Ƶ��Ӿ������
 * ��������ͼ��С���塢�������뻨ɫͼ��ȡ�
 *
 * ʹ�ó�����
 * - ��Ϸ��ʼ���׶μ��ؿ������ݲ�չʾ�ڳ����С�
 * - �ṩ����¼���ƥ���жϡ�����������ʵ�����
 */
class CardSprite : public cocos2d::Node {

public:
    /**
     * @brief ����һ�ſ��ƾ���ʵ����
     * @param face ������1~13��
     * @param suit ��ɫ��0~3��
     * @return �����ɹ����ؿ���ʵ��ָ�룬���򷵻� nullptr��
     */
    static CardSprite* create(int face, int suit);

    /**
     * @brief ��ʼ�����ƾ��顣
     * @param face ����
     * @param suit ��ɫ
     * @return ��ʼ���Ƿ�ɹ�
     */
    virtual bool init(int face, int suit);

    /**
     * @brief ��ȡ���Ƶ�����
     * @return ���ؿ��Ƶ�����1~13��
     */
    int getCardFace() const { return _face; }

    /**
     * @brief ��ȡ���ƻ�ɫ��
     * @return ���ؿ��ƻ�ɫ��0~3��
     */
    int getCardSuit() const { return _suit; }

private:
    int _face;  ///< ���Ƶ�����1~13��
    int _suit;  ///< ���ƻ�ɫ��0~3��

    cocos2d::Sprite* _bg;         ///< ���Ʊ�������
    cocos2d::Sprite* _smallFace;  ///< С���徫�飨���Ͻǣ�
    cocos2d::Sprite* _bigFace;    ///< �����徫�飨���룩
    cocos2d::Sprite* _suitIcon;   ///< ��ɫͼ�꣨���Ͻǣ�

    /**
     * @brief �������ƵĿ���Ԫ�أ�����������С���塢�����塢��ɫͼ��ȡ�
     */
    void buildCard();
};

#endif // __CARD_SPRITE_H__

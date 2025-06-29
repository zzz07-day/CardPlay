#pragma once
#ifndef __PLAYCARDS_CONTROLLER_H__
#define __PLAYCARDS_CONTROLLER_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include <vector>

/**
 * @struct MoveRecord
 * @brief ��ʾһ���ƶ������ļ�¼������֧�ֻ��˻��ơ�
 *
 * �����������Ƶ�λ�á������ڵ��Լ�֮ǰ�Ķ���״̬��
 */
struct MoveRecord {
    CardSprite* card;                  ///< ���ƶ��Ŀ���
    cocos2d::Vec2 fromPos;             ///< ԭʼλ�ã����ڶ������ˣ�
    cocos2d::Node* fromParent;         ///< ԭʼ���ڵ㣨��������ʱ����һ�㣩
    CardSprite* prevTopCard;           ///< �ƶ�֮ǰ�Ķ��ƿ��ƣ����ڻ���ʱ�ָ���
};

/**
 * @class PlayCardsController
 * @brief �������࣬����ֽ����Ϸ�еĽ����¼���������߼�����
 *
 * ������þ�̬������װ���Ŀ����߼���
 * - ���������ƥ���߼���
 * - ��������������߼���
 * - ���˲����߼���
 *
 * ʹ�÷�ʽ���� PlayCards �������ø���̬�����������¼��󶨡�
 */
class PlayCardsController {
public:
    /**
     * @brief Ϊ���������ư󶨵���¼���ʵ�ֵ���ƥ�����滻�߼���
     *
     * ƥ���߼����ж�������������Ƿ��붥�����Ƶ������1��������㣬���ƶ�������������״̬��
     *
     * @param parent ��ǰ������������ڵ㡣
     * @param _playfieldCards �������е����п��ơ�
     * @param _handStack �������еĿ���ջ��
     * @param _topCard ��ǰ�������ƣ�����ƥ���жϡ�
     * @param _undoStack ������¼ջ������֧�ֻ��ˡ�
     */
    static void bindPlayfieldEvents(cocos2d::Node* parent,
        const std::vector<CardSprite*>& _playfieldCards,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard,
        std::vector<MoveRecord>& _undoStack);

    /**
     * @brief Ϊ�������󶨵���¼���ʵ�ַ��Ƶ������߼���
     *
     * ��ҵ������ʱ������ѡ�����ƶ�Ϊ�µĶ������ƣ�����¼������
     *
     * @param parent ��ǰ����������ڵ㡣
     * @param _handStack ����������ջ��
     * @param _topCard ��ǰ�����������á�
     * @param _undoStack ������¼ջ��
     */
    static void bindStackEvents(cocos2d::Node* parent,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard,
        std::vector<MoveRecord>& _undoStack);

    /**
     * @brief ִ�л��˲����������һ�ο����ƶ���ԭ��
     *
     * �������ݰ���������λ�á������㼶�ָ����������ƻع���
     *
     * @param _undoStack �洢�Ĳ�����¼ջ��
     * @param _topCard ��ǰ�����������ã��ᱻ�滻����һ��״̬��
     */
    static void undoLastMove(std::vector<MoveRecord>& _undoStack, CardSprite*& _topCard);
};

#endif // __PLAYCARDS_CONTROLLER_H__

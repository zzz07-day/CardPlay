#pragma once
#ifndef __DRAW_PLAY_CARDS_H__
#define __DRAW_PLAY_CARDS_H__

#include "cocos2d.h"

/**
 * @namespace DrawLayout
 * @brief ������ͼ�㲼����صĳ�����
 *
 * ������ƿ�ߡ���������������ĸ߶ȣ����ڿ��ƽ��沼�֡�
 */
namespace DrawLayout {
    constexpr float kDesignWidth = 1080.0f;       ///< ��Ϸ��Ʒֱ��ʿ��
    constexpr float kDesignHeight = 2080.0f;      ///< ��Ϸ��Ʒֱ��ʸ߶�
    constexpr float kMainAreaHeight = 1500.0f;    ///< �������߶�
    constexpr float kDeckAreaHeight = 580.0f;     ///< �������߶�
}

/**
 * @class DrawPlayCards
 * @brief ��ͼ���ƹ����࣬���ڹ���ֽ����Ϸ�����еı�������Ͱ�ť�˵���
 *
 * �������з�����Ϊ��̬������������ͼ������������ظ�����ʹ�ã��ṩ��������Ļ��ƺͰ�ť���ܡ�
 */
class DrawPlayCards {
public:
    /**
     * @brief ������������������
     * @param width �����ȣ�ͨ��Ϊ��ƿ�ȣ���
     * @param height ����߶ȣ��������߶ȣ���
     * @param origin ��Ļ���½�ԭ�����ꡣ
     * @return cocos2d::LayerColor* ������������ͼ�㡣
     */
    static cocos2d::LayerColor* createMainArea(float width, float height, cocos2d::Vec2 origin);

    /**
     * @brief ������������������
     * @param width �����ȣ�ͨ��Ϊ��ƿ�ȣ���
     * @param height ����߶ȣ��������߶ȣ���
     * @param origin ��Ļ���½�ԭ�����ꡣ
     * @return cocos2d::LayerColor* �����Ķ�����ͼ�㡣
     */
    static cocos2d::LayerColor* createDeckArea(float width, float height, cocos2d::Vec2 origin);

    /**
     * @brief ���� Undo ��ť�˵���
     * @param callback ��ť�����Ļص�������
     * @param position �˵���ť����Ļλ�á�
     * @return cocos2d::Menu* ������ť�Ĳ˵��ؼ���
     */
    static cocos2d::Menu* createUndoMenu(const std::function<void(cocos2d::Ref*)>& callback, cocos2d::Vec2 position);
};

#endif // __DRAW_PLAY_CARDS_H__

#pragma once
#ifndef __CARD_SERVICE_H__
#define __CARD_SERVICE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include <vector>

/**
 * @class CardService
 * @brief ������࣬������ز������ؿ������ļ����������ƶ���
 *
 * CardService ���װ���뿨�����ݼ�����ص��߼���
 * ����� JSON �ļ��ж�ȡ������Ϣ����ʼ�����������������ͳ�ʼ���ƶ���
 *
 * ʹ�ó�����
 * - ��Ϸ��ʼ���׶ε��ã����ڼ��عؿ����ã��� level1.json����
 * - ��ģ����������ͼ����룬ʵ�ֽ��
 */
class CardService {
public:
    /**
     * @brief �������ļ�����һ�ؿ��Ŀ������ݡ�
     *
     * �ú���������ָ�� JSON �ļ�������ʼ�����������ơ������������Լ���������ָ�롣
     *
     * @param filename JSON �����ļ�·�����������ԴĿ¼���� "config/level1.json"����
     * @param _playfieldCards [out] �����������������������������顣
     * @param _handStack [out] �����������������������������顣
     * @param _topCard [out] ��ʼ����������ָ�룬�ᱻ����Ϊ�����������һ�ſ��ơ�
     *
     * @return true ���سɹ���false ����ʧ�ܻ��ʽ����
     */
    static bool loadLevelData(const std::string& filename,
        std::vector<CardSprite*>& _playfieldCards,
        std::vector<CardSprite*>& _handStack,
        CardSprite*& _topCard);
};

#endif // __CARD_SERVICE_H__

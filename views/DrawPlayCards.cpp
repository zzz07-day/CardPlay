#include "DrawPlayCards.h"

USING_NS_CC;
using namespace DrawLayout;

/**
 * @brief ��������������ͼ�㡣
 *
 * ��������ʾ�����ϵĿ�ƥ�俨�ơ�������ɫΪ��ɫϵ����������Ļ�Ϸ�����
 *
 * @param width ͼ���ȣ�ͨ��Ϊ��ƿ�ȡ�
 * @param height ͼ��߶ȣ�ȡ kMainAreaHeight��
 * @param origin ��Ļ���½�ԭ�����ꡣ
 * @return LayerColor* �����õ������������㡣
 */
LayerColor* DrawPlayCards::createMainArea(float width, float height, Vec2 origin) {
    auto backgroundLayer = LayerColor::create(Color4B(180, 120, 60, 255), width, height);
    backgroundLayer->setPosition(origin.x, origin.y + kDeckAreaHeight);  // �����ڶ���֮��
    return backgroundLayer;
}

/**
 * @brief ��������������ͼ�㡣
 *
 * ��ʾ��ҵĶ��ƣ��緭�ƶѣ�������Ϊ��ɫ��������Ļ�ײ���
 *
 * @param width ͼ���ȣ�ͨ��Ϊ��ƿ�ȡ�
 * @param height ͼ��߶ȣ�ȡ kDeckAreaHeight��
 * @param origin ��Ļ���½�ԭ�����ꡣ
 * @return LayerColor* �����õĶ����������㡣
 */
LayerColor* DrawPlayCards::createDeckArea(float width, float height, Vec2 origin) {
    auto backgroundLayer = LayerColor::create(Color4B(128, 0, 128, 255), width, height);
    backgroundLayer->setPosition(origin.x, origin.y);  // λ����Ļ�ײ�
    return backgroundLayer;
}

/**
 * @brief ������Undo��������ť�˵���
 *
 * ���ڰ󶨻��˲������������ô���Ļص�������
 *
 * @param callback ��ť����ص�������
 * @param position ��ť����Ļ�ϵ�λ�á�
 * @return Menu* ������ť�Ĳ˵�ʵ������ֱ�Ӽ��볡���С�
 */
Menu* DrawPlayCards::createUndoMenu(const std::function<void(Ref*)>& callback, Vec2 position) {
    auto undoLabel = Label::createWithSystemFont("Undo", "Arial", 36);
    auto undoItem = MenuItemLabel::create(undoLabel, callback);
    undoItem->setPosition(position);

    auto undoMenu = Menu::create(undoItem, nullptr);
    undoMenu->setPosition(Vec2::ZERO);  // �ò˵����������������
    return undoMenu;
}

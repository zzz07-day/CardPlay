#include "CardSprite.h"

/**
 * @brief ������������������ʼ��һ�� CardSprite ʵ����
 * @param face ���Ƶ�����1~13��
 * @param suit ���ƻ�ɫ��0~3��
 * @return ���ش����ɹ��� CardSprite ָ�룬ʧ�ܷ��� nullptr��
 */
CardSprite* CardSprite::create(int face, int suit) {
    CardSprite* ret = new (std::nothrow) CardSprite();
    if (ret && ret->init(face, suit)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

/**
 * @brief ��ʼ���������ݡ�
 * @param face ����
 * @param suit ��ɫ
 * @return ��ʼ���ɹ����� true�����򷵻� false��
 */
bool CardSprite::init(int face, int suit) {
    if (!Node::init()) return false;

    _face = face;
    _suit = suit;

    buildCard();  // �������ƵĿ���Ԫ��
    return true;
}

/**
 * @brief ��������ͼ�񣨱�����С���塢�����塢��ɫͼ�꣩��
 */
void CardSprite::buildCard() {
    // 1. �����������ƾ���
    _bg = Sprite::create("card_general.png");
    _bg->setAnchorPoint(Vec2(0.0f, 0.0f));
    _bg->setPosition(Vec2(0, 0));
    this->addChild(_bg);

    // 2. ���� CardSprite ��С��ê�㡢���ű���
    this->setContentSize(_bg->getContentSize());
    this->setAnchorPoint(Vec2(0.5f, 0.5f)); // ����ê�㣬���������Ż򶯻�
    this->setScale(0.7f);

    // 3. ���ݻ�ɫ��ֵת�����ַ��������ڼ���ͼƬ��Դ
    std::string suitStr, colorStr;
    switch (_suit) {
    case CST_CLUBS:    suitStr = "club";    colorStr = "black"; break;
    case CST_DIAMONDS: suitStr = "diamond"; colorStr = "red";   break;
    case CST_HEARTS:   suitStr = "heart";   colorStr = "red";   break;
    case CST_SPADES:   suitStr = "spade";   colorStr = "black"; break;
    default:           suitStr = "none";    colorStr = "black"; break;
    }

    // 4. ���ݵ���������ʾ�ı�
    std::string faceStr;
    if (_face == 1) faceStr = "A";
    else if (_face == 11) faceStr = "J";
    else if (_face == 12) faceStr = "Q";
    else if (_face == 13) faceStr = "K";
    else faceStr = StringUtils::format("%d", _face);

    // 5. ����С����ͼ�꣨���Ͻ���ʾ��
    std::string smallPath = StringUtils::format("number/small_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    _smallFace = Sprite::create(smallPath);
    if (_smallFace) {
        _smallFace->setAnchorPoint(Vec2(0, 1));  // ���ϽǶ���
        _smallFace->setPosition(Vec2(12, _bg->getContentSize().height - 10));
        _bg->addChild(_smallFace);
    }

    // 6. ���ش�����ͼ�꣨�������ģ�
    std::string bigPath = StringUtils::format("number/big_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    _bigFace = Sprite::create(bigPath);
    if (_bigFace) {
        _bigFace->setPosition(_bg->getContentSize() / 2); // ������ʾ
        _bg->addChild(_bigFace);
    }

    // 7. ���ػ�ɫͼ�꣨���Ͻǣ�
    std::string suitPath = StringUtils::format("suits/%s.png", suitStr.c_str());
    _suitIcon = Sprite::create(suitPath);
    if (_suitIcon) {
        _suitIcon->setAnchorPoint(Vec2(1, 1)); // ���ϽǶ���
        _suitIcon->setPosition(Vec2(_bg->getContentSize().width - 12, _bg->getContentSize().height - 10));
        _bg->addChild(_suitIcon);
    }
}

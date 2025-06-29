#include "CardSprite.h"

/**
 * @brief 工厂方法：创建并初始化一个 CardSprite 实例。
 * @param face 卡牌点数（1~13）
 * @param suit 卡牌花色（0~3）
 * @return 返回创建成功的 CardSprite 指针，失败返回 nullptr。
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
 * @brief 初始化卡牌内容。
 * @param face 点数
 * @param suit 花色
 * @return 初始化成功返回 true，否则返回 false。
 */
bool CardSprite::init(int face, int suit) {
    if (!Node::init()) return false;

    _face = face;
    _suit = suit;

    buildCard();  // 构建卡牌的可视元素
    return true;
}

/**
 * @brief 构建卡牌图像（背景、小字体、大字体、花色图标）。
 */
void CardSprite::buildCard() {
    // 1. 创建背景卡牌精灵
    _bg = Sprite::create("card_general.png");
    _bg->setAnchorPoint(Vec2(0.0f, 0.0f));
    _bg->setPosition(Vec2(0, 0));
    this->addChild(_bg);

    // 2. 设置 CardSprite 大小、锚点、缩放比例
    this->setContentSize(_bg->getContentSize());
    this->setAnchorPoint(Vec2(0.5f, 0.5f)); // 中心锚点，适用于缩放或动画
    this->setScale(0.7f);

    // 3. 根据花色数值转换成字符串，用于加载图片资源
    std::string suitStr, colorStr;
    switch (_suit) {
    case CST_CLUBS:    suitStr = "club";    colorStr = "black"; break;
    case CST_DIAMONDS: suitStr = "diamond"; colorStr = "red";   break;
    case CST_HEARTS:   suitStr = "heart";   colorStr = "red";   break;
    case CST_SPADES:   suitStr = "spade";   colorStr = "black"; break;
    default:           suitStr = "none";    colorStr = "black"; break;
    }

    // 4. 根据点数构造显示文本
    std::string faceStr;
    if (_face == 1) faceStr = "A";
    else if (_face == 11) faceStr = "J";
    else if (_face == 12) faceStr = "Q";
    else if (_face == 13) faceStr = "K";
    else faceStr = StringUtils::format("%d", _face);

    // 5. 加载小字体图标（左上角显示）
    std::string smallPath = StringUtils::format("number/small_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    _smallFace = Sprite::create(smallPath);
    if (_smallFace) {
        _smallFace->setAnchorPoint(Vec2(0, 1));  // 左上角对齐
        _smallFace->setPosition(Vec2(12, _bg->getContentSize().height - 10));
        _bg->addChild(_smallFace);
    }

    // 6. 加载大字体图标（卡牌中心）
    std::string bigPath = StringUtils::format("number/big_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    _bigFace = Sprite::create(bigPath);
    if (_bigFace) {
        _bigFace->setPosition(_bg->getContentSize() / 2); // 居中显示
        _bg->addChild(_bigFace);
    }

    // 7. 加载花色图标（右上角）
    std::string suitPath = StringUtils::format("suits/%s.png", suitStr.c_str());
    _suitIcon = Sprite::create(suitPath);
    if (_suitIcon) {
        _suitIcon->setAnchorPoint(Vec2(1, 1)); // 右上角对齐
        _suitIcon->setPosition(Vec2(_bg->getContentSize().width - 12, _bg->getContentSize().height - 10));
        _bg->addChild(_suitIcon);
    }
}

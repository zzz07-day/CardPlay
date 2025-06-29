#include "CardService.h"
#include "json/document.h"

USING_NS_CC;
using namespace rapidjson;

/**
 * @brief 加载卡牌关卡配置并初始化主牌区和堆牌区卡牌对象。
 *
 * @param filename JSON 配置文件路径。
 * @param _playfieldCards [out] 主牌区卡牌容器。
 * @param _handStack [out] 堆牌区卡牌容器。
 * @param _topCard [out] 初始顶部卡牌指针。
 *
 * @return true 加载成功，false 加载失败（如文件格式或内容错误）。
 */
bool CardService::loadLevelData(const std::string& filename,
    std::vector<CardSprite*>& _playfieldCards,
    std::vector<CardSprite*>& _handStack,
    CardSprite*& _topCard) {

    // 读取 JSON 文件内容
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(filename);

    Document doc;
    doc.Parse<0>(jsonStr.c_str());

    // 判断解析是否成功
    if (doc.HasParseError()) {
        CCLOG("JSON Parse Error");
        return false;
    }

    // ----------- 处理 Playfield（主牌区）数据 -----------
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const auto& pf = doc["Playfield"];
        for (SizeType i = 0; i < pf.Size(); ++i) {
            int face = pf[i]["CardFace"].GetInt();        // 卡牌点数
            int suit = pf[i]["CardSuit"].GetInt();        // 卡牌花色
            float x = pf[i]["Position"]["x"].GetFloat();  // 位置X
            float y = pf[i]["Position"]["y"].GetFloat();  // 位置Y

            // 创建卡牌对象并设置位置
            auto card = CardSprite::create(face + 1, suit);  // face+1 转换为 A~K
            card->setPosition(Vec2(x, y));
            _playfieldCards.push_back(card);
        }
    }

    // ----------- 处理 Stack（堆牌区）数据 -----------
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const auto& st = doc["Stack"];
        float baseX = 300, baseY = 300, spacing = 110;
        float drawX = baseX;

        for (SizeType i = 0; i < st.Size(); ++i) {
            int face = st[i]["CardFace"].GetInt();
            int suit = st[i]["CardSuit"].GetInt();
            auto card = CardSprite::create(face + 1, suit);

            // 最后一张作为顶牌，其余卡牌按间距排列
            if (i < st.Size() - 1) {
                card->setPosition(Vec2(drawX, baseY));
                drawX += spacing;
            }
            else {
                float topX = baseX + 350;
                card->setPosition(Vec2(topX, baseY));
                _topCard = card;
            }

            _handStack.push_back(card);
        }
    }

    return true;
}

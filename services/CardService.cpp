#include "CardService.h"
#include "json/document.h"

USING_NS_CC;
using namespace rapidjson;

/**
 * @brief ���ؿ��ƹؿ����ò���ʼ���������Ͷ��������ƶ���
 *
 * @param filename JSON �����ļ�·����
 * @param _playfieldCards [out] ����������������
 * @param _handStack [out] ����������������
 * @param _topCard [out] ��ʼ��������ָ�롣
 *
 * @return true ���سɹ���false ����ʧ�ܣ����ļ���ʽ�����ݴ��󣩡�
 */
bool CardService::loadLevelData(const std::string& filename,
    std::vector<CardSprite*>& _playfieldCards,
    std::vector<CardSprite*>& _handStack,
    CardSprite*& _topCard) {

    // ��ȡ JSON �ļ�����
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(filename);

    Document doc;
    doc.Parse<0>(jsonStr.c_str());

    // �жϽ����Ƿ�ɹ�
    if (doc.HasParseError()) {
        CCLOG("JSON Parse Error");
        return false;
    }

    // ----------- ���� Playfield�������������� -----------
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const auto& pf = doc["Playfield"];
        for (SizeType i = 0; i < pf.Size(); ++i) {
            int face = pf[i]["CardFace"].GetInt();        // ���Ƶ���
            int suit = pf[i]["CardSuit"].GetInt();        // ���ƻ�ɫ
            float x = pf[i]["Position"]["x"].GetFloat();  // λ��X
            float y = pf[i]["Position"]["y"].GetFloat();  // λ��Y

            // �������ƶ�������λ��
            auto card = CardSprite::create(face + 1, suit);  // face+1 ת��Ϊ A~K
            card->setPosition(Vec2(x, y));
            _playfieldCards.push_back(card);
        }
    }

    // ----------- ���� Stack�������������� -----------
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const auto& st = doc["Stack"];
        float baseX = 300, baseY = 300, spacing = 110;
        float drawX = baseX;

        for (SizeType i = 0; i < st.Size(); ++i) {
            int face = st[i]["CardFace"].GetInt();
            int suit = st[i]["CardSuit"].GetInt();
            auto card = CardSprite::create(face + 1, suit);

            // ���һ����Ϊ���ƣ����࿨�ư��������
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

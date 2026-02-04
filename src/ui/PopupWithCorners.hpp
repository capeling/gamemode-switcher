#pragma once

// ty HJFod

enum class Corner {
    None,
    Blue,
    Gold,
    Gray,
    Dark,
    Brown,
};

class PopupWithCorners : public geode::Popup {
private:
    static const char* getCorner(Corner corner) {
        switch (corner) {
            default:
            case Corner::None:  return nullptr;
            case Corner::Blue:  return "rewardCorner_001.png";
            case Corner::Gold:  return "dailyLevelCorner_001.png";
            case Corner::Gray:  return "dailyLevelCorner-gray.png"_spr;
            case Corner::Dark:  return "dailyLevelCorner-dark.png"_spr;
            case Corner::Brown: return "dailyLevelCorner-brown.png"_spr;
        }
    }

protected:
    void addCorners(Corner top, Corner bottom) {
        if (auto bottomSpr = getCorner(bottom)) {
            auto cornerBL = cocos2d::CCSprite::createWithSpriteFrameName(bottomSpr);
            FLAlertLayer::m_mainLayer->addChildAtPosition(cornerBL, geode::Anchor::BottomLeft, ccp(24.75f, 24.75f));

            auto cornerBR = cocos2d::CCSprite::createWithSpriteFrameName(bottomSpr);
            cornerBR->setFlipX(true);
            FLAlertLayer::m_mainLayer->addChildAtPosition(cornerBR, geode::Anchor::BottomRight, ccp(-24.75f, 24.75f));
        }
        if (auto topSpr = getCorner(top)) {
            auto cornerTL = cocos2d::CCSprite::createWithSpriteFrameName(topSpr);
            cornerTL->setFlipY(true);
            FLAlertLayer::m_mainLayer->addChildAtPosition(cornerTL, geode::Anchor::TopLeft, ccp(24.75f, -24.75f));

            auto cornerTR = cocos2d::CCSprite::createWithSpriteFrameName(topSpr);
            cornerTR->setFlipY(true);
            cornerTR->setFlipX(true);
            FLAlertLayer::m_mainLayer->addChildAtPosition(cornerTR, geode::Anchor::TopRight, ccp(-24.75f, -24.75f));
        }
    }
};

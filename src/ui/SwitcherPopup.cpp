#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <ui/SwitcherPopup.hpp>
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

SwitcherPopup* SwitcherPopup::create() {
    SwitcherPopup* ret = new SwitcherPopup();
    if(ret->initAnchored(400, 240, "geode.loader/GE_square02.png")) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool SwitcherPopup::setup() {
    setTitle("Edit Player", "bigFont.fnt");
    addCorners(Corner::Blue, Corner::Blue);

    auto closeSpr = ButtonSprite::create("OK");
    closeSpr->setScale(0.9f);
    setCloseButtonSpr(closeSpr);

    m_closeBtn->setPosition(m_mainLayer->getContentWidth() / 2, 25);

    m_gamemodeMenu = CCMenu::create();
    m_gamemodeMenu->setLayout(RowLayout::create()->setGap(15));
    m_mainLayer->addChildAtPosition(m_gamemodeMenu, Anchor::Center, ccp(0, 60));

    m_speedMenu = CCMenu::create();
    m_speedMenu->setLayout(RowLayout::create()->setGap(15));
    m_mainLayer->addChildAtPosition(m_speedMenu, Anchor::Center, ccp(0, 5));

    m_miscMenu = CCMenu::create();
    m_miscMenu->setLayout(RowLayout::create()->setGap(15));
    m_mainLayer->addChildAtPosition(m_miscMenu, Anchor::Center, ccp(0, -50));

    m_localGamemodeState = HookPlayLayer::get()->getCurrentPlayerState();
    m_localSpeedState = HookPlayLayer::get()->getCurrentBoostState();

    m_gamemodeBtns = {
        createGamemode("gj_iconBtn_on_001.png",   "gj_iconBtn_off_001.png",   0),
        createGamemode("gj_shipBtn_on_001.png",   "gj_shipBtn_off_001.png",   1),
        createGamemode("gj_ballBtn_on_001.png",   "gj_ballBtn_off_001.png",   2),
        createGamemode("gj_birdBtn_on_001.png",   "gj_birdBtn_off_001.png",   3),
        createGamemode("gj_dartBtn_on_001.png",   "gj_dartBtn_off_001.png",   4),
        createGamemode("gj_robotBtn_on_001.png",  "gj_robotBtn_off_001.png",  5),
        createGamemode("gj_spiderBtn_on_001.png", "gj_spiderBtn_off_001.png", 6),
        createGamemode("gj_swingBtn_on_001.png",  "gj_swingBtn_off_001.png",  7)
    };

    m_speedBtns = {
        createSpeed("boost_01_001.png", 8),
        createSpeed("boost_02_001.png", 9),
        createSpeed("boost_03_001.png", 10),
        createSpeed("boost_04_001.png", 11),
        createSpeed("boost_05_001.png", 12)
    };
    
    m_miscBtns = {
        createMiscToggler("platOn.png"_spr,    "platOff.png"_spr,    13),
        createMiscToggler("sizeOn.png"_spr,    "sizeOff.png"_spr,    14),
        createMiscToggler("gravOn.png"_spr,    "gravOff.png"_spr,    15),
        createMiscToggler("reverseOn.png"_spr, "reverseOff.png"_spr, 16),
        createMiscToggler("portalOn.png"_spr,  "portalOff.png"_spr,  17)
    };

    for(const auto& btn : m_gamemodeBtns) {
        if(!btn) continue;
        m_gamemodeMenu->addChild(btn);
    }
    m_gamemodeMenu->updateLayout();

    for(const auto& btn : m_speedBtns) {
        if(!btn) continue;
        m_speedMenu->addChild(btn);
    }
    m_speedMenu->updateLayout();

    for(const auto& btn : m_miscBtns) {
        if(!btn) break;
        m_miscMenu->addChild(btn);
    }
    m_miscMenu->updateLayout();

    return true;
}

void SwitcherPopup::onClose(CCObject* sender) {
    HookPlayLayer::get()->performActionsOnPlayer(std::span{m_actions});
    Popup::onClose(sender);
}

geode::Ref<CCMenuItemSpriteExtra> SwitcherPopup::createGamemode(const char* spriteOn, const char* spriteOff, int action) {
    geode::Ref<CCMenuItemSpriteExtra> ret = CCMenuItemExt::createSpriteExtraWithFrameName(spriteOff, 0.9f, [this](CCObject* sender){
        m_actions[0] = static_cast<Action>(sender->getTag());
        m_localGamemodeState = sender->getTag();
        updateGamemodeButtons();
    });

    ret->setTag(action);

    auto disabledImage = CCSprite::createWithSpriteFrameName(spriteOn);
    disabledImage->setScale(0.9f);
    
    ret->setDisabledImage(disabledImage);
    ret->setEnabled(action != m_localGamemodeState);

    return ret;
}

geode::Ref<CCMenuItemSpriteExtra> SwitcherPopup::createSpeed(const char* sprite, int action) {
    auto normalImage = CCSprite::createWithSpriteFrameName(sprite);
    normalImage->setScale(0.85f);
    normalImage->setOpacity(150);

    geode::Ref<CCMenuItemSpriteExtra> ret = CCMenuItemExt::createSpriteExtra(normalImage, [this](CCObject* sender){
        m_actions[1] = static_cast<Action>(sender->getTag());
        m_localSpeedState = sender->getTag();
        updateSpeedButtons();
    });

    ret->setTag(action);
    auto disabledImage = CCSprite::createWithSpriteFrameName(sprite);
    disabledImage->setScale(0.85f);

    ret->setDisabledImage(disabledImage);
    ret->setEnabled(action != m_localSpeedState + 8);
    return ret;
}

geode::Ref<CCMenuItemToggler> SwitcherPopup::createMiscToggler(const char* spriteOn, const char* spriteOff, int action) {
    geode::Ref<CCMenuItemToggler> ret = CCMenuItemExt::createTogglerWithFrameName(spriteOn, spriteOff, 0.9f, [this](auto sender){
        if(m_actions[sender->getTag() - 11] == static_cast<Action>(sender->getTag())) m_actions[sender->getTag() - 11] = static_cast<Action>(-1);
        else m_actions[sender->getTag() - 11] = static_cast<Action>(sender->getTag());
        //updateMiscButtons();
    });

    ret->setTag(action);

    auto disabledImage = CCSprite::createWithSpriteFrameName(spriteOn);
    disabledImage->setScale(0.9f);

    ret->toggle(disabledImage);
    switch(action) {
        case 13: ret->toggle(HookPlayLayer::get()->m_player1->m_isPlatformer); break;
        case 14: ret->toggle(HookPlayLayer::get()->m_player1->m_vehicleSize == 0.6f); break;
        case 15: ret->toggle(HookPlayLayer::get()->m_player1->m_isUpsideDown); break;
        case 16: ret->toggle(HookPlayLayer::get()->m_player1->m_isGoingLeft); break;
        case 17: ret->toggle(HookPlayLayer::get()->m_fields->m_portalsEnabled); break;
        default: ret->toggle(false); break;
    }
    return ret;
}

void SwitcherPopup::updateGamemodeButtons() {
    for(const auto& btn : m_gamemodeBtns) {
        btn->setEnabled(btn->getTag() != m_localGamemodeState);
    }
}

void SwitcherPopup::updateSpeedButtons() {
    for(const auto& btn : m_speedBtns) {
        btn->setEnabled(btn->getTag() != m_localSpeedState);
    }
}

}

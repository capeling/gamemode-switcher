#pragma once

#include <ui/PopupWithCorners.hpp>

#include <enums.hpp>

namespace switcher {

class SwitcherPopup : public PopupWithCorners {
public:
    static SwitcherPopup* create();
    bool init() override;
    
    void updateGamemodeButtons();
    void updateSpeedButtons();

    int getCurrentAction();

    void onClose(cocos2d::CCObject*) override;

    geode::Ref<CCMenuItemSpriteExtra> createGamemode(const char* spriteOn, const char* spriteOff, int action);
    geode::Ref<CCMenuItemSpriteExtra> createSpeed(const char* sprite, int action);
    geode::Ref<CCMenuItemToggler> createMiscToggler(const char* spriteOn, const char* spriteOff, int action);

protected:
    std::vector<geode::Ref<CCMenuItemSpriteExtra>> m_gamemodeBtns = {};
    cocos2d::CCMenu* m_gamemodeMenu = nullptr;

    std::vector<geode::Ref<CCMenuItemSpriteExtra>> m_speedBtns = {};
    cocos2d::CCMenu* m_speedMenu = nullptr;

    std::vector<geode::Ref<CCMenuItemToggler>> m_miscBtns = {};
    cocos2d::CCMenu* m_miscMenu = nullptr;

    std::vector<geode::Ref<CCMenuItemSpriteExtra>> m_playerBtns = {};
    cocos2d::CCMenu* m_playerMenu = nullptr;

    std::vector<Action> m_actions = {Action::None, Action::None, Action::None, Action::None, Action::None, Action::None, Action::None};

    int m_localGamemodeState = 0;
    int m_localSpeedState = 0;
};

}

#pragma once

#include <Geode/modify/PlayLayer.hpp>

#include <enums.hpp>

namespace switcher {

struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
    struct Fields {
        bool m_portalsEnabled = true;
    };

    int getCurrentPlayerState();
    int getCurrentBoostState();

    void performActionsOnPlayer(std::span<Action> actions);
    inline void performActionOnPlayer(Action action);

    static HookPlayLayer* get();
};

}
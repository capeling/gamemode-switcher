#pragma once

#include <Geode/modify/GJBaseGameLayer.hpp>

namespace switcher {

struct HookGJBaseGameLayer : geode::Modify<HookGJBaseGameLayer, GJBaseGameLayer> {
    struct Fields {
        bool m_isPlayLayer = false;
    };

    bool init();
    bool canBeActivatedByPlayer(PlayerObject* p0, EffectGameObject* p1);
    bool isPortalType(GameObjectType type);
};

}
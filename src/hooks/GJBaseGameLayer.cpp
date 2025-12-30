#include <hooks/GJBaseGameLayer.hpp>
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

bool HookGJBaseGameLayer::canBeActivatedByPlayer(PlayerObject* p0, EffectGameObject* p1) {
    if(m_fields->m_isPlayLayer) {
        if(isPortalType(p1->m_objectType) && !HookPlayLayer::get()->m_fields->m_portalsEnabled) {
            return false;
        }
    }
    return GJBaseGameLayer::canBeActivatedByPlayer(p0, p1);
}

bool HookGJBaseGameLayer::init() {
    if(!GJBaseGameLayer::init()) {
        return false;
    }

    m_fields->m_isPlayLayer = typeinfo_cast<PlayLayer*>(this) != nullptr;
    return true;
}

bool HookGJBaseGameLayer::isPortalType(GameObjectType type) {
    return type == GameObjectType::CubePortal || type == GameObjectType::ShipPortal
        || type == GameObjectType::BallPortal || type == GameObjectType::UfoPortal  
        || type == GameObjectType::WavePortal || type == GameObjectType::RobotPortal 
        || type == GameObjectType::SpiderPortal || type == GameObjectType::SwingPortal
        || type == GameObjectType::TeleportPortal || type == GameObjectType::DualPortal
        || type == GameObjectType::GravityTogglePortal || type == GameObjectType::NormalMirrorPortal
        || type == GameObjectType::InverseMirrorPortal || type == GameObjectType::InverseGravityPortal
        || type == GameObjectType::NormalGravityPortal || type == GameObjectType::MiniSizePortal
        || type == GameObjectType::RegularSizePortal || type == GameObjectType::SoloPortal;
}

}
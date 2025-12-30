#include "enums.hpp"
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

int HookPlayLayer::getCurrentPlayerState() {
    if(m_player1->isInNormalMode()) return 0;
    else if(m_player1->m_isShip) return 1;
    else if(m_player1->m_isBall) return 2;
    else if(m_player1->m_isBird) return 3;
    else if(m_player1->m_isDart) return 4;
    else if(m_player1->m_isRobot) return 5;
    else if(m_player1->m_isSpider) return 6;
    else if(m_player1->m_isSwing) return 7;

    return -1;
}

int HookPlayLayer::getCurrentBoostState() {
    float speed = m_player1->m_playerSpeed;

    if(speed == 0.7f) return 0;
    if(speed == 0.9f) return 1;
    if(speed == 1.1f) return 2;
    if(speed == 1.3f) return 3;
    if(speed == 1.6f) return 4;

    return -1;
}

HookPlayLayer* HookPlayLayer::get() {
    return static_cast<HookPlayLayer*>(GameManager::get()->m_playLayer);
}

void HookPlayLayer::performActionsOnPlayer(std::span<Action> actions) {
    for(const auto& action : actions) {
        performActionOnPlayer(action);
    }
}

void HookPlayLayer::performActionOnPlayer(Action action) {
    switch(action) {
        using enum Action;
        // 0-7 gamemode actions
        case Cube: {
            m_player1->toggleFlyMode(false, false);
            m_player1->toggleRollMode(false, false);
            m_player1->toggleBirdMode(false, false);
            m_player1->toggleDartMode(false, false);
            m_player1->toggleRobotMode(false, false);
            m_player1->toggleSpiderMode(false, false);
            m_player1->toggleSwingMode(false, false);
            break;
        }
        case Ship: {
            m_player1->toggleFlyMode(true, true);
            break;
        }
        case Ball: {
            m_player1->toggleRollMode(true, true);
            break;
        }
        case Bird: {
            m_player1->toggleBirdMode(true, true);
            break;
        }
        case Dart: {
            m_player1->toggleDartMode(true, true);
            break;
        }
        case Robot: {
            m_player1->toggleRobotMode(true, true);
            break;
        }
        case Spider: {
            m_player1->toggleSpiderMode(true, true);
            break;
        }
        case Swing: {
            m_player1->toggleSwingMode(true, true);
            break;
        }

        case Speed0p5x: {
            m_player1->m_playerSpeed = 0.7f;
            break;
        }
        case Speed1x: {
            m_player1->m_playerSpeed = 0.9f;
            break;
        }
        case Speed2x: {
            m_player1->m_playerSpeed = 1.1f;
            break;
        }
        case Speed3x: {
            m_player1->m_playerSpeed = 1.3f;
            break;
        }
        case Speed4x: {
            m_player1->m_playerSpeed = 1.6f;
            break;
        }

        //13-17 misc
        case PlatformerToggle: {
            m_player1->m_isPlatformer = !m_player1->m_isPlatformer;
#ifdef GEODE_IS_ANDROID
            m_uiLayer->togglePlatformerMode(m_player1->m_isPlatformer);
#endif
            break;
        }
        case ScaleToggle: {
            m_player1->togglePlayerScale(m_player1->m_vehicleSize != 0.6f, true);
            break;
        }
        case GravityToggle: {
            m_player1->flipGravity(!m_player1->m_isUpsideDown, true);
            break;
        }
        case ReverseToggle: {
            m_player1->doReversePlayer(!m_player1->m_isGoingLeft);
            break;
        }
        case PortalsToggle: {
            m_fields->m_portalsEnabled = !m_fields->m_portalsEnabled;
            break;
        }

        default:
            break;
    }

    if(static_cast<int>(action) <= 7 && action != Action::None) {
        auto obj = TeleportPortalObject::create("edit_eGameRotBtn_001.png", true);
        obj->m_cameraIsFreeMode = true;
        this->playerWillSwitchMode(m_player1, obj);
    }
}

}
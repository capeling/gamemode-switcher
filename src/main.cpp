#include <ui/SwitcherPopup.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    struct HookPauseLayer : Modify<HookPauseLayer, PauseLayer> {
        void customSetup() {
            PauseLayer::customSetup();

            auto rightMenu = typeinfo_cast<CCMenu*>(this->getChildByID("right-button-menu"));
            if(!rightMenu) {
                log::error("right-button-menu not found!");
                return;
            }

            auto button = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_editModeBtn_001.png", 0.675f, [=](CCObject*) {
                switcher::SwitcherPopup::create()->show();
            });

            button->setID("gamemode-editor-button"_spr);

            rightMenu->addChild(button);
            rightMenu->updateLayout();
        }
    };
}
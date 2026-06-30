#include <Geode/Geode.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

namespace {
    constexpr char const* kSaveKey = "invisible-objects-enabled";

    bool enabled() {
        return Mod::get()->getSavedValue<bool>(kSaveKey, false);
    }

    void setEnabled(bool value) {
        Mod::get()->setSavedValue(kSaveKey, value);
    }
}

class $modify(InvisibleObjectsPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto menu = CCMenu::create();
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu, 1000);

        this->createToggleButton(
            "Invisible Objects",
            menu_selector(InvisibleObjectsPauseLayer::onToggleInvisibleObjects),
            enabled(),
            menu,
            { winSize.width / 2.f, 36.f }
        );
    }

    void onToggleInvisibleObjects(CCObject*) {
        setEnabled(!enabled());
    }
};

class $modify(InvisibleObjectsGameObject, GameObject) {
    void visit() {
        if (enabled() && !typeinfo_cast<PlayerObject*>(this)) {
            return;
        }

        GameObject::visit();
    }
};

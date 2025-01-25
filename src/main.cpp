#include "./includes.h"
#include <Geode/modify/MenuLayer.hpp>

#include "./DevelopersPageManager.h"
#include "./ErrorsManager/ErrorsManager.h"

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		DevelopersPageManager::getInstance()->onMenuLayer(this);
		ErrorsManager::onMenuLayer(this);
		return true;
	}
};
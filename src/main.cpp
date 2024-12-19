#include "./includes.h"
#include <Geode/modify/MenuLayer.hpp>

#include "./DevelopersPageManager.h"

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		DevelopersPageManager::getInstance()->onMenuLayer(this);
		return true;
	}
};
#include "./ErrorsManager.h"
#include "./ErrorsPopup.h"

ErrorsManager* ErrorsManager::getInstance() {
	auto saved = GameManager::get()->getChildByID("gdps-pack-errors-manager");
	if (saved) {
		std::cout << "save found" << std::endl;
		return static_cast<ErrorsManager*>(saved);
	}
	std::cout << "created" << std::endl;
	auto newManager = new ErrorsManager();
	newManager->setID("gdps-pack-errors-manager");
	GameManager::get()->addChild(newManager);
	return newManager;
}

void ErrorsManager::addError(const std::string& label, ErrorType type) {
	ErrorsManager::getInstance()->errors.push_back(std::make_pair(label, type));
}

std::vector<std::pair<std::string, ErrorsManager::ErrorType>> ErrorsManager::getErrors() {
	return ErrorsManager::getInstance()->errors;
}


void ErrorsManager::onOpenErrorsPopup(CCObject*) {
	ErrorsPopup::create()->show();
}

void ErrorsManager::onMenuLayer(MenuLayer* layer) {
	if (getInstance()->errors.size() > 0 && !layer->getChildByID("gdps-pack-errors-menu")) {
		auto size = CCDirector::sharedDirector()->getWinSize();

		auto menu = CCMenu::create();
		menu->setID("gdps-pack-errors-menu");
		menu->setPosition(50, size.height - 50);
		layer->addChild(menu);

		auto button = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("exMark_001.png"), layer, menu_selector(ErrorsManager::onOpenErrorsPopup));
		menu->addChild(button);
	}
}
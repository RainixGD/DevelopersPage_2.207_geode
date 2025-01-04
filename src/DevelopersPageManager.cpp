#include "./DevelopersPageManager.h"
#include "./structs.h"
#include "./DevelopersPopup.h"

void DevelopersPageManager::init() {
	loadingStatus = loadData();
}

bool DevelopersPageManager::isValidURL(const std::string& url) {
	std::regex url_regex(R"(^https?://)");
	return std::regex_search(url, url_regex);
}

DevelopersPageManager::DataLoadingResult DevelopersPageManager::loadData() {

	std::ifstream file("Resources/devPanel.json");
	if (!file) return FileNotFound;
	std::ostringstream buffer;
	buffer << file.rdbuf();
	std::string fileContent = buffer.str();

	file.close();

	try {
		auto root = nlohmann::json::parse(fileContent);
		if (!root.is_array()) return ParsingError;

		for (auto developer : root) {
			if (!developer.contains("name") || !developer["name"].is_string() ||
				!developer.contains("role") || !developer["role"].is_string() ||
				!developer.contains("logo") || !developer["logo"].is_string() ||
				!developer.contains("buttons") || !developer["buttons"].is_array()) return ParsingError;

			auto developerData = new DeveloperData();
			developerData->name = developer["name"];
			developerData->role = developer["role"];
			developerData->logo = developer["logo"];


			auto buttons = developer["buttons"];
			if (buttons.size() > 6) return TooManyButtons;
			for (auto btn : buttons) {
				if (!btn.contains("texture") || !btn["texture"].is_string()
					|| !btn.contains("link") || !btn["link"].is_string()) return ParsingError;

				auto socialNetworkData = new DeveloperSocialNetworkData;
				socialNetworkData->texture = btn["texture"];
				socialNetworkData->link = btn["link"];
				if (!isValidURL(socialNetworkData->link)) return InvalidUrl;

				developerData->socialNetworks.push_back(socialNetworkData);
			}

			data.push_back(developerData);
		}
	}
	catch (...) {
		return ParsingError;
	}
	return OK;
}

void DevelopersPageManager::onDevelopersBtn(CCObject*) {
	DevelopersPopup::create(DevelopersPageManager::getInstance()->data)->show();
}

void DevelopersPageManager::onMenuLayer(MenuLayer* layer) {

	if (loadingStatus != OK) {

		std::string errorText;
		switch (loadingStatus) {
		case FileNotFound:
			errorText = "Can't find 'devPanel.json' in ./Resources";
			break;
		case ParsingError:
			errorText = "Can't parse 'devPanel.json'";
			break;
		case TooManyButtons:
			errorText = "Too many buttons in 'devPanel.json'";
			break;
		case InvalidUrl:
			errorText = "Links for buttons should start with 'http://' or 'https://' in 'devPanel.json'";
			break;
		}

		auto size = CCDirector::sharedDirector()->getWinSize();

		auto errorLabel = CCLabelBMFont::create(errorText.c_str(), "bigFont.fnt");
		errorLabel->setColor({ 255, 0, 0 });
		errorLabel->setScale(0.6);
		errorLabel->setPosition({ size.width / 2, size.height - 10 });
		layer->addChild(errorLabel);

		return;
	}

	auto moreGamesMenu = layer->getChildByID("more-games-menu");

	auto devSprite = CCSprite::create("developers.png");
	if (devSprite == NULL)
		devSprite = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	devSprite->setScale(1.5);
	auto devBtn = CCMenuItemSpriteExtra::create(devSprite, layer, menu_selector(DevelopersPageManager::onDevelopersBtn));
	devBtn->setPosition(static_cast<CCNode*>(moreGamesMenu->getChildren()->objectAtIndex(0))->getPosition());

	moreGamesMenu->removeAllChildren();

	moreGamesMenu->addChild(devBtn);
}

DevelopersPageManager* DevelopersPageManager::getInstance() {
	if (!instance) {
		instance = new DevelopersPageManager();
		instance->init();
	}
	return instance;
}

DevelopersPageManager* DevelopersPageManager::instance = nullptr;
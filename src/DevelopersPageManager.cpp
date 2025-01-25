#include "./DevelopersPageManager.h"
#include "./structs.h"
#include "./DevelopersPopup.h"
#include "./ErrorsManager/ErrorsManager.h"

void DevelopersPageManager::init() {
	isOk = loadData();
}

bool DevelopersPageManager::isValidURL(const std::string& url) {
	std::regex url_regex(R"(^https?://)");
	return std::regex_search(url, url_regex);
}

bool DevelopersPageManager::hasFileExtension(const std::string& fileName, const std::string& extension) {
	std::string pattern = ".*\\." + extension + "$";
	std::regex regexPattern(pattern, std::regex::icase);

	return std::regex_match(fileName, regexPattern);
}

bool DevelopersPageManager::loadData() {

    std::ifstream file("Resources/devPanel.json");
    if (!file) {
        ErrorsManager::addError("Developers Page: can't find 'Resources/devPanel.json'! File not found or permission denied.", ErrorsManager::Error);
        return false;
    }

    std::ostringstream buffer;
    try {
        buffer << file.rdbuf();
    }
    catch (const std::ios_base::failure& e) {
        ErrorsManager::addError("Developers Page: failed to read the file 'Resources/devPanel.json'. IOError: " + std::string(e.what()), ErrorsManager::Error);
        file.close();
        return false;
    }

    std::string fileContent = buffer.str();
    file.close();

    if (fileContent.empty()) {
        ErrorsManager::addError("Developers Page: 'Resources/devPanel.json' is empty!", ErrorsManager::Error);
        return false;
    }

    try {
        auto root = nlohmann::json::parse(fileContent);

        if (!root.is_array()) {
            ErrorsManager::addError("Developers Page: JSON root element should be an array, but got a " + std::string(root.type_name()) + ".", ErrorsManager::Error);
            return false;
        }

        for (auto developer : root) {
            if (!developer.contains("name") || !developer["name"].is_string()) {
                ErrorsManager::addError("Developers Page: Missing or invalid 'name' property in one of the developers.", ErrorsManager::Error);
                return false;
            }

            if (!developer.contains("role") || !developer["role"].is_string()) {
                ErrorsManager::addError("Developers Page: Missing or invalid 'role' property in one of the developers.", ErrorsManager::Error);
                return false;
            }

            if (!developer.contains("logo") || !developer["logo"].is_string()) {
                ErrorsManager::addError("Developers Page: Missing or invalid 'logo' property in one of the developers.", ErrorsManager::Error);
                return false;
            }

            if (!developer.contains("buttons") || !developer["buttons"].is_array()) {
                ErrorsManager::addError("Developers Page: Missing or invalid 'buttons' property in one of the developers. It should be an array.", ErrorsManager::Error);
                return false;
            }

            auto developerData = new DeveloperData();
            developerData->name = developer["name"];
            developerData->role = developer["role"];
            developerData->logo = developer["logo"];

            auto buttons = developer["buttons"];
            if (buttons.size() > 6) {
                ErrorsManager::addError("Developers Page: Too many buttons for developer (maximum allowed: 6).", ErrorsManager::Error);
                return false;
            }

            for (size_t i = 0; i < buttons.size(); ++i) {
                const auto& btn = buttons[i];
                if (!btn.contains("texture") || !btn["texture"].is_string() || !btn.contains("link") || !btn["link"].is_string()) {
                    ErrorsManager::addError("Developers Page: Missing or invalid properties in social button at index " + std::to_string(i) + ".", ErrorsManager::Error);
                    return false;
                }

                auto socialNetworkData = new DeveloperSocialNetworkData;
                socialNetworkData->texture = btn["texture"];

                if (!hasFileExtension(socialNetworkData->texture, "png")) {
                    ErrorsManager::addError("Developers Page: Texture in button at index " + std::to_string(i) + " should be a '.png' file.", ErrorsManager::Error);
                    return false;
                }

                socialNetworkData->link = btn["link"];
                if (!isValidURL(socialNetworkData->link)) {
                    ErrorsManager::addError("Developers Page: Invalid URL in button at index " + std::to_string(i) + ". URL should start with 'http://' or 'https://'.", ErrorsManager::Error);
                    return false;
                }

                developerData->socialNetworks.push_back(socialNetworkData);
            }

            data.push_back(developerData);
        }

    }
    catch (const nlohmann::json::parse_error& e) {
        ErrorsManager::addError("Developers Page: JSON parse error. Exception: " + std::string(e.what()) + ". Location: " + std::to_string(e.byte) + ".", ErrorsManager::Error);
        return false;
    }
    catch (const nlohmann::json::type_error& e) {
        ErrorsManager::addError("Developers Page: JSON type error while processing data. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::bad_alloc& e) {
        ErrorsManager::addError("Developers Page: Memory allocation error. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::ios_base::failure& e) {
        ErrorsManager::addError("Developers Page: I/O operation failure. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::exception& e) {
        ErrorsManager::addError("Developers Page: Unknown error occurred. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }

    return true;
}

void DevelopersPageManager::onDevelopersBtn(CCObject*) {
	DevelopersPopup::create(DevelopersPageManager::getInstance()->data)->show();
}

void DevelopersPageManager::onMenuLayer(MenuLayer* layer) {

	if (!isOk) return;

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
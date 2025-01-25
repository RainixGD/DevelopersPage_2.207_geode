#include "./ErrorsPopup.h"
#include "./ErrorsManager.h"
#include "../Nodes/ListNode.h"

class ErrorsList : public ListNode<std::pair<std::string, ErrorsManager::ErrorType>> {
    virtual void setupCell(Cell* cell, std::pair<std::string, ErrorsManager::ErrorType> cellData, int index) {
        auto [text, errorType] = cellData;

        ccColor3B baseColor;
        if (errorType == ErrorsManager::ErrorType::Warning) {
            baseColor = ccc3(255, 215, 0);
        }
        else if (errorType == ErrorsManager::ErrorType::Error) {
            baseColor = ccc3(255, 69, 0);
        }
        else {
            baseColor = ccc3(126, 58, 0);
        }

        float shadeFactor = (index % 2 == 0) ? 1.0f : 0.85f;
        ccColor3B shadedColor = ccc3(
            baseColor.r * shadeFactor,
            baseColor.g * shadeFactor,
            baseColor.b * shadeFactor
        );

        cell->setColor(shadedColor);

        auto textArea = CCLabelBMFont::create(text.c_str(), "chatFont.fnt");
        textArea->setAnchorPoint({ 0, 1 });
        textArea->setPosition({ 10, cell->getContentSize().height - 5 });
        textArea->setWidth(cell->getContentSize().width - 50);
        textArea->setLineBreakWithoutSpace(true);
        textArea->setScale(0.45);
        cell->addChild(textArea);

        std::string iconFile = (errorType == ErrorsManager::ErrorType::Error)
            ? "GJ_deleteIcon_001.png"
            : "GJ_coinsIcon_001.png";
        auto icon = CCSprite::createWithSpriteFrameName(iconFile.c_str());
        icon->setAnchorPoint({ 1, 0.5f });
        icon->setPosition({ cell->getContentSize().width - 10, cell->getContentSize().height / 2 });
        cell->addChild(icon);
    }
public:
    static ErrorsList* create(float width, float height, float cellHeight, std::vector<std::pair<std::string, ErrorsManager::ErrorType>> data, const ccColor4B& backgroundColor) {
        auto ret = new ErrorsList();
        if (ret && ret->init(width, height, cellHeight, data, backgroundColor)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

bool ErrorsPopup::setup() {

    auto errors = ErrorsManager::getErrors();
    auto errorsList = ErrorsList::create(300, 150, 40, errors, { 100, 54, 31, 255 });
    errorsList->setPosition({ 0, 25 });
    errorsList->setScale(0.9);
    m_mainLayer->addChild(errorsList);

	return true;
}

ErrorsPopup* ErrorsPopup::create() {
	auto ret = new ErrorsPopup();
	if (ret && ret->initAnchored(300, 200)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}
#include "./DevelopersPopup.h"
#include "./DeveloperNode.h"
#include "./structs.h"

bool DevelopersPopup::setup() {
	if (devData.size() == 0) return true;

	auto nextSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
	nextSprite->setFlipX(true);
	nextButton = CCMenuItemSpriteExtra::create(nextSprite, this, menu_selector(DevelopersPopup::onNext));
	nextButton->setPosition({ 412.5, 80 });
	m_buttonMenu->addChild(nextButton);

	auto previousSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
	previousButton = CCMenuItemSpriteExtra::create(previousSprite, this, menu_selector(DevelopersPopup::onPrevious));
	previousButton->setPosition({ 22.5, 80 });
	m_buttonMenu->addChild(previousButton);

	for (auto dev : devData) {
		auto devNode = DeveloperNode::create(dev);
		devNode->setPosition(217.5, 80);
		m_mainLayer->addChild(devNode);
		this->devNodes.push_back(devNode);
	}

	updateDevNodes();
	updateControlButtons();

	return true;
}

void DevelopersPopup::updateControlButtons() {
	nextButton->setVisible(selectedDev == devNodes.size() - 1 ? 0 : 1);
	previousButton->setVisible(selectedDev == 0 ? 0 : 1);
}

void DevelopersPopup::updateDevNodes() {
	for (int i = 0; i < devNodes.size(); i++)
		devNodes[i]->setVisible(i == selectedDev ? 1 : 0);
}

void DevelopersPopup::onNext(CCObject*) {
	if (selectedDev < devData.size() - 1) {
		selectedDev++;
	}
	updateDevNodes();
	updateControlButtons();
}

void DevelopersPopup::onPrevious(CCObject*) {
	if (selectedDev > 0) {
		selectedDev--;
	}
	updateDevNodes();
	updateControlButtons();
}

DevelopersPopup* DevelopersPopup::create(const std::vector<DeveloperData*>& devData) {
	auto ret = new DevelopersPopup();
	ret->devData = devData;
	if (ret && ret->initAnchored(435, 160)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
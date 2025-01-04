#include "./DeveloperNode.h"
#include "./SocialNetworkButton.h"
#include "./structs.h"

bool DeveloperNode::init(DeveloperData* devData) {
	if (!CCNode::init()) return false;

	auto devName = CCLabelBMFont::create(devData->name.c_str(), "bigFont.fnt");
	devName->setPosition({ 80, 40 });
	devName->limitLabelWidth(240, 1, 0.1);
	this->addChild(devName);

	auto devRole = CCLabelBMFont::create(devData->role.c_str(), "goldFont.fnt");
	devRole->setPosition({ 80, 15 });
	devRole->limitLabelWidth(175, 1, 0.1);
	this->addChild(devRole);

	auto devLogo = CCSprite::create(devData->logo.c_str());
	if (devLogo == NULL) {
		devLogo = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
		devLogo->setScale(2.5);
	}
	devLogo->setPosition({ -100, 0 });
	this->addChild(devLogo);

	auto menu = CCMenu::create();
	menu->setPosition(80, -25);
	this->addChild(menu);

	for (auto socialNetwork : devData->socialNetworks) {
		auto socialNetworkBtnSprite = CCSprite::create(socialNetwork->texture.c_str());
		if (socialNetworkBtnSprite == NULL)
			socialNetworkBtnSprite = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
		socialNetworkBtnSprite->setContentSize({ 30.5, 30.5 });
		auto devBtn = SocialNetworkButton::create(socialNetworkBtnSprite, socialNetwork->link);
		menu->addChild(devBtn);
	}

	menu->alignItemsHorizontallyWithPadding(10);

	return true;
}

DeveloperNode* DeveloperNode::create(DeveloperData* devData) {
	auto ret = new DeveloperNode;
	if (ret && ret->init(devData)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}
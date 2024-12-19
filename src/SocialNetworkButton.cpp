#include "./SocialNetworkButton.h"

void SocialNetworkButton::onClick(CCObject*) {
	CCApplication::sharedApplication()->openURL(link.c_str());
}

bool SocialNetworkButton::init(CCSprite* sprite, const std::string& link) {
	if (!CCMenuItemSpriteExtra::init(sprite, sprite, this, menu_selector(SocialNetworkButton::onClick))) return false;

	this->link = link;

	return true;
}

SocialNetworkButton* SocialNetworkButton::create(CCSprite* sprite, const std::string& link) {
	auto ret = new SocialNetworkButton();
	if (ret && ret->init(sprite, link)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}
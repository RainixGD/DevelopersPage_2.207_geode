#pragma once
#include "./includes.h"

class SocialNetworkButton : public CCMenuItemSpriteExtra {
	std::string link;

	void onClick(CCObject*);
	virtual bool init(CCSprite* sprite, const std::string& link);
public:
	static SocialNetworkButton* create(CCSprite* sprite, const std::string& link);
};
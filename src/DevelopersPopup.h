#pragma once
#include "./includes.h"

struct DeveloperData;
class DeveloperNode;

class DevelopersPopup : public geode::Popup<> {
	std::vector<DeveloperData*> devData;
	std::vector<DeveloperNode*> devNodes;
	CCMenuItemSpriteExtra* nextButton;
	CCMenuItemSpriteExtra* previousButton;
	int selectedDev = 0;
protected:
	bool setup() override;

	void updateControlButtons();
	void updateDevNodes();

	void onNext(CCObject*);
	void onPrevious(CCObject*);
public:
	static DevelopersPopup* create(const std::vector<DeveloperData*>& devData);
};
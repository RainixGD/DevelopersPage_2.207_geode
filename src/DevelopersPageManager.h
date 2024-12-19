#pragma once
#include "./includes.h"

struct DeveloperData;

class DevelopersPageManager {

	enum DataLoadingResult {
		OK,
		FileNotFound,
		ParsingError,
		TooManyButtons
	};

	std::vector<DeveloperData*> data;
	DataLoadingResult loadingStatus;
	static DevelopersPageManager* instance;

	void init();

	DataLoadingResult loadData();

	DevelopersPageManager() {};
public:
	void onDevelopersBtn(CCObject*);
	void onMenuLayer(MenuLayer* layer);
	static DevelopersPageManager* getInstance();

};
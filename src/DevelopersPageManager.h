#pragma once
#include "./includes.h"

struct DeveloperData;

class DevelopersPageManager {

	enum DataLoadingResult {
		OK,
		FileNotFound,
		ParsingError,
		TooManyButtons,
		InvalidUrl
	};

	std::vector<DeveloperData*> data;
	DataLoadingResult loadingStatus;
	static DevelopersPageManager* instance;

	void init();

	bool isValidURL(const std::string& url);
	DataLoadingResult loadData();

	DevelopersPageManager() {};
public:
	void onDevelopersBtn(CCObject*);
	void onMenuLayer(MenuLayer* layer);
	static DevelopersPageManager* getInstance();

};
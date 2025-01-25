#pragma once
#include "./includes.h"

struct DeveloperData;

class DevelopersPageManager {

	bool isOk;

	std::vector<DeveloperData*> data;
	static DevelopersPageManager* instance;

	void init();

	bool isValidURL(const std::string& url);
	bool hasFileExtension(const std::string& fileName, const std::string& extension);
	bool loadData();

	DevelopersPageManager() {};
public:
	void onDevelopersBtn(CCObject*);
	void onMenuLayer(MenuLayer* layer);
	static DevelopersPageManager* getInstance();

};
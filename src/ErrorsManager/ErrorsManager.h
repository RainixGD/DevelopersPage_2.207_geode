#pragma once
#include "../includes.h"

class ErrorsManager : public CCNode {
public:
	enum ErrorType {
		Warning,
		Error
	};
private:
	static ErrorsManager* instance;

	std::vector<std::pair<std::string, ErrorType>> errors = {};

public:

	static ErrorsManager* getInstance();

	static void addError(const std::string& label, ErrorType type);

	static std::vector<std::pair<std::string, ErrorType>> getErrors();


	void onOpenErrorsPopup(CCObject*);

	static void onMenuLayer(MenuLayer* layer);
};
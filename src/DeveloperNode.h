#pragma once
#include "./includes.h"

struct DeveloperData;

class DeveloperNode : public CCNode {
	virtual bool init(DeveloperData* devData);
public:
	static DeveloperNode* create(DeveloperData* devData);
};
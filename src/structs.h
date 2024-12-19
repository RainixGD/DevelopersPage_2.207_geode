#pragma once
#include "./includes.h"

struct DeveloperSocialNetworkData {
	std::string texture;
	std::string link;
};

struct DeveloperData {
	std::string name;
	std::string role;
	std::string logo;
	std::vector<DeveloperSocialNetworkData*> socialNetworks;
};
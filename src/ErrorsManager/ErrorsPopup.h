#pragma once
#include "../includes.h"

class ErrorsPopup : public Popup<> {
	virtual bool setup();
public:
	static ErrorsPopup* create();
};
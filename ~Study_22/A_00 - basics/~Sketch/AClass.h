//#pragma once

#ifndef _CODE_B_h
#define _CODE_B_h


#include "arduino.h"
#include "utils.h"

class BetaClass
{
protected:


public:
	BetaClass(byte tag = 99);
	~BetaClass();

	void init(byte tag = 1);

	void showStatus();

private:
	byte _id{};
	bool _status{ false };
	void _showStatus();

};


#endif

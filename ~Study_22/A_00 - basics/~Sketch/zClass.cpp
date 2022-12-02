//#define DBG
#include "AClass.h"



BetaClass::BetaClass(byte arg_id) : _id{ arg_id }
{
	dpr("<BetaClass - constructor>"); dtb; _showStatus(); dnl;

}

BetaClass::~BetaClass()
{
	dpr("<BetaClass - destructor>"); dtb; _showStatus(); dnl;
}

void BetaClass::init(byte tag)
{
	_status = true;
	_id = tag;
	dpr("<BetaClass:: init>      "); dtb; _showStatus(); dnl;

}

void BetaClass::showStatus()
{
	dpr("<BetaClass:: showStatus>"); dtb; _showStatus(); dnl;

}

void BetaClass::_showStatus()
{
	dpr(_id); dtb;  dpr(logic(_status));

}

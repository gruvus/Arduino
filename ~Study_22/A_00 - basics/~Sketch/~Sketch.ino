#undef DBG

//#include "utils_test_pins.h"
//#include "T1_setup.h"
#include "utils.h"
#include "AClass.h"

//myT1_t myT;


//=======================================
// class declarations => .h  
//=======================================

class AlfaClass
{
private:
	int m_value1{};
	double m_value2{};
	char m_value3{};

public:
	AlfaClass();

	void print();
};


//=======================================

void setup() {
	// default prep
	{
		Serial.begin(115200);
		Serial.print("\n Running ~Sketch "); DebugPrint("in debug mode"); NL; NL;
	}

	AlfaClass alfa_object{};
	alfa_object.print();
	dnl;

	{
		dpr("calling beta 1"); dnl;
		BetaClass beta;
		beta.showStatus();
		beta.init();
		beta.showStatus();
		dpr("done with beta 1"); dnl;

	}
	dnl;

	{
		BetaClass beta(5);
		beta.showStatus();
		beta.init(7);
		beta.showStatus();
	}
	dnl;



}

void loop() {}


//=======================================
// class definitions => .cpp  
//=======================================


AlfaClass::AlfaClass()
    : m_value1{ 1 }
    , m_value2{ 2.2 }
    , m_value3{ 'c' } // Initialize member variables
{
    // No need for assignment here
}

void AlfaClass::print()
{
    dpr("  <AlfaClass>  "); dpr(m_value1); dtb; dpr(m_value2); dtb; dpr(m_value3); dnl;
}

//-----------------------------------------------------


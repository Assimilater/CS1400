#include "Package.h"
using namespace std;

//---------------------------------------------------------------------------------+
// Constructors                                                                    |
// Manage the inital values                                                        |
//---------------------------------------------------------------------------------+
Package::Package() {
	weight = 0;
	cost_ounce = 0;
}
Package::Package(Person s, Person r, int w, double c) {
	Sender = s;
	Receiver = r;
	weight = w;
	cost_ounce = c;
}
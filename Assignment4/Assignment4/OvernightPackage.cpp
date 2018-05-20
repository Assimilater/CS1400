#include "OvernightPackage.h"

//---------------------------------------------------------------------------------+
// Constructors                                                                    |
// Manage the inital values                                                        |
//---------------------------------------------------------------------------------+
OvernightPackage::OvernightPackage() : Package() {
	differential = 0;
}
OvernightPackage::OvernightPackage(double rate) : Package() {
	differential = rate;
}
OvernightPackage::OvernightPackage(Person s, Person r, int w, double c) : Package(s, r, w, c) {
	differential = 0;
}
OvernightPackage::OvernightPackage(Person s, Person r, int w, double c, double rate) : Package(s, r, w, c) {
	differential = rate;
}
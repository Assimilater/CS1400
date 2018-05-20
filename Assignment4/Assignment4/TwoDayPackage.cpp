#include "TwoDayPackage.h"

//---------------------------------------------------------------------------------+
// Constructors                                                                    |
// Manage the inital values                                                        |
//---------------------------------------------------------------------------------+
TwoDayPackage::TwoDayPackage() : Package() {
	differential = 0;
}
TwoDayPackage::TwoDayPackage(double rate) : Package() {
	differential = rate;
}
TwoDayPackage::TwoDayPackage(Person s, Person r, int w, double c) : Package(s, r, w, c) {
	differential = 0;
}
TwoDayPackage::TwoDayPackage(Person s, Person r, int w, double c, double rate) : Package(s, r, w, c) {
	differential = rate;
}
#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H

// External Dependencies
#include "Package.h"

class TwoDayPackage : public Package {
private:
	double differential;
public:
	TwoDayPackage();
	TwoDayPackage(double);
	TwoDayPackage(Person, Person, int, double);
	TwoDayPackage(Person, Person, int, double, double);

	// Accessors and Mutators
	double GetRateIncrease() const { return differential; }
	void SetRateIncrease(double r) { differential = r; }

	// Override Package::Cost()
	double Cost() const { return (weight + differential) * cost_ounce; }
};

#endif
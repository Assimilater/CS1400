#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H

// External Dependencies
#include "Package.h"

class OvernightPackage : public Package {
private:
	double differential;
public:
	OvernightPackage();
	OvernightPackage(double);
	OvernightPackage(Person, Person, int, double);
	OvernightPackage(Person, Person, int, double, double);

	// Accessors and Mutators
	double GetRateIncrease() const { return differential; }
	void SetRateIncrease(double r) { differential = r; }

	// Override Package::Cost()
	double Cost() const { return (weight * cost_ounce) + differential; }
};

#endif
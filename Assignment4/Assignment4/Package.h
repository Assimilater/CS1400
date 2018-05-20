#ifndef PACKAGE_H
#define PACKAGE_H

// External Dependencies
#include "Person.h"

class Package {
protected:
	Person
		Sender,
		Receiver;
	int weight;
	double cost_ounce;
public:
	// Constructors and Destructor
	Package();
	Package(Person, Person, int, double);
	
	// Accessors and Mutators
	Person GetSender() const { return Sender; }
	Person GetReceiver() const { return Receiver; }
	void SetSender(Person p) { Sender = p; }
	void SetReceiver(Person p) { Receiver = p; }

	int GetWeight() const { return weight; }
	double GetRate() const { return cost_ounce; }
	void SetWeight(int w) { weight = w; }
	void SetRate(double r) { cost_ounce = r; }

	// Output Methods
	double Cost() const { return weight * cost_ounce; }
};

#endif
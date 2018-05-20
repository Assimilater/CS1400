#ifndef PERSON_H
#define PERSON_H

// External dependencies
#include <string>

class Person {
private:
	std::string
		name,
		address,
		city,
		state,
		zip;
public:
	Person() { name = ""; address = ""; city = ""; state = ""; zip = ""; }
	Person(std::string n, std::string a, std::string c, std::string s, std::string z) {
		name = n;
		address = a;
		city = c;
		state = s;
		zip = z;
	}

	void SetName(std::string s) { name = s; }
	void SetAddress(std::string s) { address = s; }
	void SetCity(std::string s) { city = s; }
	void SetState(std::string s) { state = s; }
	void SetZip(std::string s) { zip = s; }
	std::string GetName() const { return name; }
	std::string GetAddress() const { return address; }
	std::string GetCity() const { return city; }
	std::string GetState() const { return state; }
	std::string GetZip() const { return zip; }
};

#endif
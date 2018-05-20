#ifndef RATIONAL_H
#define RATIONAL_H
#include <string>
#include <iostream>

class Rational {
private:
	int numerator,
		denomenator;
	std::string to_str;

	int ComputeGCD(int, int);
	void Simplify(int&, int&);
	void update();

public:
	// Constructors and copy constructor
	Rational(int n = 0, int d = 1);
	Rational(const std::string);
	Rational(const Rational&);

	// Assignment operator
	Rational& operator=(const Rational&);
	Rational& operator=(const int); // convert an int data to its Rational representation
	Rational& operator=(const std::string);
	
	// Arithmetic binary operators
	Rational operator+(const Rational&);
	Rational operator+(const int);
	Rational operator+(const std::string);

	//Compound assignment operators
	Rational& operator+=(const Rational&);
	Rational& operator+=(const int);
	Rational& operator+=(const std::string);

	// Relational operators
	bool operator==(const Rational &);
	bool operator>(const Rational &);

	// Prefix and Postfix operators
	Rational& operator++(); // prefix ++
	Rational operator++(int); // postfix ++

	operator double(); // convert a Rational object to a double

	// Streaming output
	friend std::ostream& operator<<(std::ostream &out, const Rational &obj);
};

std::ostream& operator<<(std::ostream &out, const Rational &obj); // Recommended by Dr. Qi
std::istream& operator>>(std::istream &in, Rational &obj);

Rational operator+(const int&, const Rational&);
Rational operator+(const std::string, const Rational&);

#endif
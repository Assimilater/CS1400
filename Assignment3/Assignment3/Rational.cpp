#include "Rational.h"
using namespace std;

//Private methods
int Rational::ComputeGCD(int num, int denom) {
	int remainder = denom % num;
	while (remainder != 0) {
		denom = num;
		num = remainder;
		remainder = denom % num;
	}
	return num;
}
void Rational::Simplify(int &num, int &denom) {
	int gcd = ComputeGCD(num, denom); 
	num = num / gcd;
	denom = denom / gcd;
}
void Rational::update() {
	// Handle 0 case
	if (numerator == 0) {
		denomenator = 1;
	}
	else {
		// Reduce negative values
		if (denomenator < 0) {
			numerator *= -1;
			denomenator *= -1;
		}

		// Reduce by Greatest Common Denominator
		Simplify(numerator, denomenator);
	}

	// Update the string
	to_str = "";
	to_str.append(to_string(numerator));
	if (denomenator != 1) {
		to_str.append("/");
		to_str.append(to_string(denomenator));
	}
}

// Constructors and copy constructor
Rational::Rational(int n, int d) {
	numerator = n;
	denomenator = d;
	update();
}
Rational::Rational(const string s) {
	int s_index = s.find("/");
	if (s_index != string::npos) {
		numerator = atoi(s.substr(0, s_index).c_str());
		denomenator = atoi(s.substr(s_index + 1).c_str());
	}
	else {
		numerator = atoi(s.c_str());
		denomenator = 1;
	}
	update();
}
Rational::Rational(const Rational &obj) {
	numerator = obj.numerator;
	denomenator = obj.denomenator;
	update();
}

// Assignment operator
Rational& Rational::operator=(const Rational &obj) {
	if (this != &obj) {
		numerator = obj.numerator;
		denomenator = obj.denomenator;
		update();
	}
	return *this;
}
Rational& Rational::operator=(const int n) {
	numerator = n;
	denomenator = 1;
	update();
	return *this;
}
Rational& Rational::operator=(const string s) {
	int s_index = s.find("/");
	if (s_index != string::npos) {
		numerator = atoi(s.substr(0, s_index).c_str());
		denomenator = atoi(s.substr(s_index + 1).c_str());
	}
	else {
		numerator = atoi(s.c_str());
		denomenator = 1;
	}
	update();
	return *this;
}

// Arithmetic binary operators
Rational Rational::operator+(const Rational &obj) {
	Rational temp(*this);
	
	int num_lhs = temp.numerator,
		num_rhs = obj.numerator;

	if (temp.denomenator != obj.denomenator) {
		num_lhs *= obj.denomenator;
		num_rhs *= temp.denomenator;

		temp.denomenator *= obj.denomenator;
	}
	temp.numerator = num_lhs + num_rhs;

	temp.update();
	return temp;
}
Rational Rational::operator+(const int n) {
	Rational temp(*this);
	temp.numerator += n * denomenator;
	temp.update();
	return temp;
}
Rational Rational::operator+(const string s) {
	Rational temp(s);
	temp += *this;
	return temp;
}

// Compound assignment operators
Rational& Rational::operator+=(const Rational &obj) {
	*this = *this + obj;
	return *this;
}
Rational& Rational::operator+=(const int n) {
	*this = *this + n;
	return *this;
}
Rational& Rational::operator+=(const string s) {
	*this = *this + s;
	return *this;
}

// Relational operators
bool Rational::operator==(const Rational &obj) {
	return numerator == obj.numerator && denomenator == obj.denomenator;
}
bool Rational::operator>(const Rational &obj) {
	int num_lhs = numerator * obj.denomenator,
		num_rhs = obj.numerator * denomenator;

	return num_lhs > num_rhs;
}

// Prefix and Postfix operators
Rational& Rational::operator++() {
	// prefix ++
	*this += 1;
	return *this;
}
Rational Rational::operator++(int) {
	// postfix ++
	Rational t(*this);
	*this += 1;
	return t;
}

Rational::operator double() {
	return ((double)numerator) / denomenator;
}

// Outside functions
ostream& operator<<(ostream &out, const Rational &obj) {
	out << obj.to_str;
	return out;
}
istream& operator>>(istream &in, Rational &obj) {
	string str;
	getline(in, str);
	obj = str;
	return in;
}

// Arithmetic global operators
Rational operator+(const int &n, const Rational &obj) {
	Rational temp(obj);
	temp += n;
	return temp;
}

Rational operator+(const std::string s, const Rational &obj) {
	Rational temp(obj);
	temp += s;
	return temp;
}
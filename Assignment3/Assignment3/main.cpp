//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 3: Operator Overloading and Type Conversion                          |
//---------------------------------------------------------------------------------+
#include <iostream>
#include <sstream>
#include "Rational.h"
using namespace std;

void myDriver();
void taDriver();

int main() {
	//taDriver();
	myDriver();

	system("pause");
	return 0;
}

void myDriver() {
	Rational a;
	Rational
		b(a),
		c(3),
		d(2, 3),
		e("4 / 16");

	cout << "Constructors:" << endl
		<< a << endl
		<< b << endl
		<< c << endl
		<< d << endl
		<< e << endl
		<< endl

		<< "Input a rational value: ";
	cin >> a;
	cout << "The reduced value is: " << a << endl
		<< endl;

	a = 4;
	b = a;
	c = "3/-4";

	cout << "Assignment Operators:" << endl
		<< a << endl
		<< b << endl
		<< c << endl
		<< endl;

	a += c;
	b += "1/2";
	c += 2;

	cout << "Compound Operators:" << endl
		<< a << endl
		<< b << endl
		<< c << endl
		<< endl;

	d = 2;
	e = "-1/3";

	a = d + e;
	b = d + string("1/2");
	c = e + 3;

	cout << "Arithmetic Operators:" << endl
		<< a << endl
		<< b << endl
		<< c << endl
		<< endl;

	a = d + e;
	b = string("1/2") + d;
	c = 3 + e;

	cout << "Outside Arithmetic Operators:" << endl
		<< a << endl
		<< b << endl
		<< c << endl
		<< endl;

	a = Rational("-1/2");
	b = Rational("1/3");

	cout << "Prefix: " << ++a << endl;
	cout << "Value after: " << a << endl
		<< endl

		<< "Postfix: " << b++ << endl;
	cout << "Value after: " << b << endl
		<< endl

		<< "Boolean Operators:" << endl
		<< (a == Rational("1/2") ? "true" : "false") << endl
		<< (a == Rational(1, -2) ? "true" : "false") << endl
		<< (b == Rational(4, 3) ? "true" : "false") << endl
		<< (b > Rational(3, 4) ? "true" : "false") << endl
		<< endl;

	cout << "Casting as Double: " << (double)(a + 1) << endl;
}

void taDriver() {
	Rational a;
	cout << "Rational a using Rational(); = " << a << endl;//a=0
	cout << endl;
	a = 0;
	Rational b(5);
	cout << "Rational b using Rational(int 5); = " << b << endl;//b=5
	cout << endl;
	b = 5;
	Rational c(5, 6);
	cout << "Rational c using Rational(int 5, int 6); = " << c << endl;// 5/6
	cout << endl;
	Rational d("8/21");
	cout << "Rational d using Rational(string \"8/21\"); = " << d << endl;// 8/21
	cout << endl;
	Rational e("8/20");
	cout << "Rational e using Rational(string \"8/20\"); with a fraction that simplifies = " << e << endl;// 2/5
	cout << endl;

	Rational f(e);
	cout << "Rational f using Rational(const Rational &e); = " << f << endl;// 2/5
	cout << endl;

	f = d;
	cout << "f=d --> f=" << f << endl;// 8/21
	cout << endl;

	f = 5;
	cout << "f=5 --> f=" << f << endl;// 5
	cout << endl;

	f = "5/8";
	cout << "f=\"5/8\" --> f=" << f << endl;// 5/8
	cout << endl;

	Rational g;
	g = b + c;
	cout << "b + c = " << g << endl;// 35/6
	cout << endl;

	g = d + 3;
	cout << "d + 3 = " << g << endl;// 71/21
	cout << endl;


	g = d + string("-1/21");
	cout << "d + string(\"-1/21\") = " << g << endl;// 1/3
	cout << endl;

	b += c;
	cout << "b+=c --> b=" << b << endl;// 35/6
	cout << endl;
	b = 5;

	c += 3;
	cout << "c+=3 --> c=" << c << endl;// 23/6
	cout << endl;
	c = "5/6";


	d += string("-1/21");
	cout << "d+=string(\"-1/21\") --> d= " << d << endl;// 1/3
	cout << endl;
	d = "8/21";

	cout << a++ << endl;// a=0
	a = 0;
	cout << ++a << endl;// 1
	a = 0;

	d = c + string("4/10");// 37/30
	cout << d << endl;

	e = string("1/2") + b;// 11/2
	cout << e << endl;

	e = string("11/2");

	Rational x(-2, 3);
	cout << x << endl;// -2/3

	double y = c;
	cout << y << endl;//0.8333

	cout << "input a rational number:";
	cin >> a;// input 6/8
	cout << a << endl;// 3/4
	cout << "if b > c then output \"it worked\": ";
	if (b>c) {
		cout << " > worked\n";
	}
}
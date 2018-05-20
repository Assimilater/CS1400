#include "Circle.h"
using namespace std;

// Protected Methods
void Circle::Copy2D(const Circle& rho) {
	Copy(rho.name, "Circle");
	radius = rho.radius;
}

// Constructors and operator=
Circle::Circle() : Geometry("Unnamed Circle", "Circle") {
	radius = 0;
}
Circle::Circle(const char* name, int r) : Geometry(name, "Circle") {
	radius = r;
}
Circle::Circle(const Circle& rho) : Geometry(rho.name, "Circle") {
	radius = rho.radius;
}
Circle& Circle::operator=(const Circle& rho) {
	Copy2D(rho);
	return *this;
}

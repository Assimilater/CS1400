#include "Triangle.h"
using namespace std;

// Protected methods
void Triangle::Copy2D(const Triangle& rho) {
	Copy(rho.name, "Triangle");
	side = rho.side;
}

// Constructors, Destructor and operator=
Triangle::Triangle() : Geometry("Unnamed Triangle", "Triangle") {
	side = 0;
}
Triangle::Triangle(const char* name, double s) : Geometry(name, "Triangle") {
	side = s;
}
Triangle::Triangle(const Triangle& rho) : Geometry(rho.name, "Triangle") {
	side = rho.side;
}
Triangle& Triangle::operator=(const Triangle& rho) {
	Copy2D(rho);
	return *this;
}

// Calculated virtual method
double Triangle::ComputeSurface() const {
	// Area of an equilateral triangle: S^2 * sqrt(3)/4
	return side * side * sqrt(3) / 4;
}
#include "Prism.h"
using namespace std;

// Protected methods
void Prism::Copy3D(const Prism& rho) {
	Copy2D(rho);
	SetType("Prism");
	height = rho.height;
}

// Constructors and operator=
Prism::Prism() : Triangle("Unnamed Prism", 0) {
	height = 0;
	SetType("Prism");
}
Prism::Prism(const char* name, double s, double h) : Triangle(name, s) {
	height = h;
	SetType("Prism");
}
Prism::Prism(const Prism& rho) : Triangle(rho) {
	Copy3D(rho);
}
Prism& Prism::operator=(const Prism& rho) {
	Copy3D(rho);
	return *this;
}

// Calculated virtual functions
double Prism::ComputeVolume() const {
	return Triangle::ComputeSurface() * height;
}
double Prism::ComputeSurface() const {
	return (2 * Triangle::ComputeSurface()) + (3 * side * height);
}

#include "Sphere.h"
using namespace std;

// Protected methods
void Sphere::Copy3D(const Sphere& rho) {
	Copy2D(rho);
	SetType("Sphere");
}

// Constructors and operator=
Sphere::Sphere() : Circle("Unnamed Sphere", 0) {
	SetType("Sphere");
}
Sphere::Sphere(const char* name, int r) : Circle(name, r) {
	SetType("Sphere");
}
Sphere::Sphere(const Sphere& rho) : Circle(rho) {
	Copy3D(rho);
}
Sphere& Sphere::operator=(const Sphere& rho) {
	Copy3D(rho);
	return *this;
}

// Calculated virtual functions
double Sphere::ComputeVolume() const {
	return (M_PI * radius * radius * radius * 4) / 3;
}
double Sphere::ComputeSurface() const {
	return M_PI * radius * radius * 4;
}

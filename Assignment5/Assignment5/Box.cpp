#include "Box.h"
using namespace std;

// Protected methods
void Box::Copy3D(const Box& rho) {
	Copy2D(rho);
	SetType("Box");
	height = rho.height;
}

// Constructors and operator=
Box::Box() : Rectangle("Unnamed Box", 0, 0) {
	height = 0;
	SetType("Box");
}
Box::Box(const char* name, int w, int l, int h) : Rectangle(name, w, l) {
	height = h;
	SetType("Box");
}
Box::Box(const Box& rho) : Rectangle(rho) {
	Copy3D(rho);
}
Box& Box::operator=(const Box& rho) {
	Copy3D(rho);
	return *this;
}

// Calculated virtual functions
double Box::ComputeVolume() const {
	return width * length * height;
}
double Box::ComputeSurface() const {
	return
		(2 * width * length) +
		(2 * length * height) +
		(2 * height * width);
}

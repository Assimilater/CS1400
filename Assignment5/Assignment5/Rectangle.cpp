#include "Rectangle.h"
using namespace std;

// Protected Methods
void Rectangle::Copy2D(const Rectangle& rho) {
	Copy(rho.name, "Rectangle");
	width = rho.width;
	length = rho.length;
}

// Constructors and operator=
Rectangle::Rectangle() : Geometry("Unnamed Rectangle", "Rectangle") {
	width = 0;
	length = 0;
}
Rectangle::Rectangle(const char* name, int w, int l) : Geometry(name, "Rectangle") {
	width = w;
	length = l;
}
Rectangle::Rectangle(const Rectangle& rho) : Geometry(rho.name, "Rectangle") {
	width = rho.width;
	length = rho.length;
}
Rectangle& Rectangle::operator=(const Rectangle& rho) {
	Copy2D(rho);
	return *this;
}

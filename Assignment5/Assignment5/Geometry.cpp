#include "Geometry.h"
using namespace std;

// Protected methods to reduce duplicate code
void Geometry::SetName(const char* s) {
	if (name != NULL) { delete name; name = NULL; }

	int len = strlen(s) + 1;
	name = new char[len];
	strcpy_s(name, len, s);
}
void Geometry::SetType(const char* s) {
	if (type != NULL) { delete type; type = NULL; }

	int len = strlen(s) + 1;
	type = new char[len];
	strcpy_s(type, len, s);
}
void Geometry::Copy(const char* n, const char* t) {
	SetName(n);
	SetType(t);
}

// Constructor and Destructor
Geometry::Geometry(const char* name, const char* type) {
	Copy(name, type);
}
Geometry::~Geometry() {
	if (name != NULL) { delete[] name; type = NULL; }
	if (type != NULL) { delete[] type; type = NULL; }
}
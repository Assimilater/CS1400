//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 5: Abstract Base Class and Dynamic Binding                           |
//---------------------------------------------------------------------------------+
#include "Report.h"
using namespace std;

int main() {
	const int GEOMETRY_COUNT = 6;
	Geometry *Shapes[GEOMETRY_COUNT];
	for (int i = 0; i < GEOMETRY_COUNT; i++) {
		Shapes[i] = NULL;
	}

	Shapes[0] = new Circle("Sir Cumference", 12);
	Shapes[1] = new Sphere("Mr. Apple", 5);
	Shapes[2] = new Triangle("Ms. Lateral", 5);
	Shapes[3] = new Prism("Mrs. Triangle", 4, 8);
	Shapes[4] = new Rectangle("Cat", 4, 5);
	Shapes[5] = new Rectangle("Dog", 4, 5);
	
	// Print out the master report
	report(Shapes, GEOMETRY_COUNT);

	// Clean up
	for (int i = 0; i < GEOMETRY_COUNT; i++) {
		if (Shapes[i] != NULL) {
			delete Shapes[i];
			Shapes[i] = NULL;
		}
	}
	system("pause");
	system("cls");

	// Test copy constructors and overloaded operator= methods for each derived class
	Box a("Dog", 3, 4, 5);
	Rectangle b(a);
	report(&b);

	system("pause");
	system("cls");

	Sphere c("Cat", 5);
	Circle d("Leapoard", 12);
	d = c;
	report(&d);

	system("pause");
	system("cls");

	Prism e("Lion", 10, 5);
	Triangle f(e);
	report(&f);

	system("pause");
	return 0;
}

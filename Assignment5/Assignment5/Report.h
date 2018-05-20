#ifndef REPORT_H
#define REPORT_H

// External dependencies
#include <iostream>
#include <iomanip>

// Include all Geometry classes
#include "Geometry.h"
#include "Circle.h"
#include "Sphere.h"
#include "Rectangle.h"
#include "Box.h"
#include "Triangle.h"
#include "Prism.h"

// Swap template (so same function is used for int* and double* in BubbleSort)
template <typename T>
void Swap(T &a, T &b) {
	T c = a;
	a = b;
	b = c;
}

// Data-value array manipulators
void BubbleSort(double*, int*, int, bool);
double median(const double*, int); // Requires the array passed to be sorted
double mean(const double*, int);

void report(Geometry**, int);
void report(const Geometry*);

#endif

#ifndef PRISM_H
#define PRISM_H

#include "Triangle.h"

class Prism : public Triangle {
private:
	double height;
	void Copy3D(const Prism&);
public:
	Prism();
	Prism(const char*, double, double);
	Prism(const Prism&);
	Prism& operator=(const Prism&);

	double GetHeight() { return height; }
	void SetHeight(double h) { height = h; }

	double ComputeVolume() const;
	double ComputeSurface() const;
};

#endif

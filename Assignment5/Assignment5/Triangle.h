#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Geometry.h"

class Triangle : public Geometry {
protected:
	double side;
	void Copy2D(const Triangle& rho);

public:
	Triangle();
	Triangle(const char*, double);
	Triangle(const Triangle&);
	Triangle& operator=(const Triangle& rho);

	double GetSideLength() { return side; }
	void SetSideLength(double s) { side = s; }

	virtual double ComputeVolume() const { return 0; }
	virtual double ComputeSurface() const;
};

#endif

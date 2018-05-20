#ifndef CIRCLE_H
#define CIRCLE_H

#include "Geometry.h"

class Circle : public Geometry {
protected:
	double radius;
	void Copy2D(const Circle&);
public:
	Circle();
	Circle(const char*, int);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	double GetRadius() { return radius; }
	void SetRadius(double r) { radius = r; }

	virtual double ComputeVolume() const { return 0; }
	virtual double ComputeSurface() const { return M_PI * radius * radius; }
};

#endif

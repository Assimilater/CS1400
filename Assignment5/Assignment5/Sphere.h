#ifndef SPHERE_H
#define SPHERE_H

#include "Circle.h"

class Sphere : public Circle {
private:
	void Copy3D(const Sphere&);
public:
	Sphere();
	Sphere(const char*, int);
	Sphere(const Sphere&);
	Sphere& operator=(const Sphere&);

	virtual double ComputeVolume() const;
	virtual double ComputeSurface() const;
};

#endif

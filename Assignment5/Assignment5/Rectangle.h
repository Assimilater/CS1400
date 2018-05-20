#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Geometry.h"

class Rectangle : public Geometry {
protected:
	double width, length;
	void Copy2D(const Rectangle&);
public:
	Rectangle();
	Rectangle(const char*, int, int);
	Rectangle(const Rectangle&);
	virtual Rectangle& operator=(const Rectangle&);

	double GetWidth() { return width; }
	double GetLength() { return length; }
	void SetWidth(double w) { width = w; }
	void SetLength(double l) { length = l; }

	virtual double ComputeVolume() const { return 0; }
	virtual double ComputeSurface() const { return width * length; }
};

#endif

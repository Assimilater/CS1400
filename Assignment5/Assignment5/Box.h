#ifndef BOX_H
#define BOX_H

#include "Rectangle.h"

class Box : public Rectangle {
protected:
	double height;
	void Copy3D(const Box&);
public:
	Box();
	Box(const char*, int, int, int);
	Box(const Box&);
	Box& operator=(const Box&);

	double GetHeight() { return height; }
	void SetHeight(double h) { height = h; }

	virtual double ComputeVolume() const;
	virtual double ComputeSurface() const;
};

#endif

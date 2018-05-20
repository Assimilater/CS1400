#ifndef GEOMETRY_H
#define GEOMETRY_H

// Because cmath won't define M_PI consistently when _USE_MATH_DEFINES is defined...
#define M_PI 3.1415926535897932384626433832795
#include <iostream>
#include <cmath>

class Geometry {
protected:
	char
		*name,
		*type;

	void SetType(const char*);
	void SetName(const char*);
	void Copy(const char*, const char*);

public:
	// Constructors and Destructor
	Geometry(const char*, const char*);
	~Geometry();

	// Accessors
	const char* GetName() const { return name; }
	const char* GetType() const { return type; }

	// Abstract Calculated Methods
	virtual double ComputeVolume() const = 0;
	virtual double ComputeSurface() const = 0;
};

#endif

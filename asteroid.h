#pragma once
#include "moveable.h"

#define ROTATION		6

class Asteroid : public Moveable
{
public:
	Asteroid(int x, int y, double dx, double dy) : Moveable(x, y, dx, dy)
	{
	};
	~Asteroid()					{};

	void draw();

private:
	int rotation;
};


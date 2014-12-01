#pragma once
#include "moveable.h"

#define ROTATION		6

class Ship : public Moveable
{
public:
	Ship(int x, int y, double dx, double dy) : Moveable(x, y, dx, dy), rotation(0)    {};
	~Ship()					{};

	void draw();

	int getRotation()	{ return rotation; };

	void rotateLeft()	{ rotation += ROTATION; };
	void rotateRight()	{ rotation -= ROTATION; };

	void rocketBurst();

private:
	int rotation;
};


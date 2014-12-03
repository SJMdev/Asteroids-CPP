#pragma once
#include "moveable.h"

class Asteroid : public Moveable
{
public:
	Asteroid(int x, int y, double dx, double dy) : Moveable(x, y, dx, dy, false), radius(8)
	{
		//std::cout << "Asteroid was just created that has a wrap of: " << path.getWrap() << std::endl;
	};
	~Asteroid()					{};

	void draw();
	bool readyToDie() { return this->path.isDead(); }
	int getRadius() { return this->radius; }
private:
	int radius;
};


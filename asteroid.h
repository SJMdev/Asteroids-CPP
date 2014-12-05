#pragma once
#include "moveable.h"

class Asteroid : public Moveable
{
public:
	Asteroid(int x, int y, double dx, double dy, int id, int objectX, int objectY) : Moveable(x, y, dx, dy, false, objectX, objectY), radius(objectY), id(id)
	{
		//std::cout << "Asteroid was just created that has a wrap of: " << path.getWrap() << std::endl;
	};
	~Asteroid()					{ };

	void draw();
	bool readyToDie() { return this->path.isDead(); }
	int getRadius() { return this->radius; }
	int id;
private:
	int radius;
};


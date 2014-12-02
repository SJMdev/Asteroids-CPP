#pragma once
#include "moveable.h"

class Asteroid : public Moveable
{
public:
	Asteroid(int x, int y, double dx, double dy) : Moveable(x, y, dx, dy, false)
	{
		//std::cout << "Asteroid was just created that has a wrap of: " << path.getWrap() << std::endl;
	};
	~Asteroid()					{};

	void draw();

private:
};


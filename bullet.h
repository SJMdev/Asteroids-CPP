#pragma once
#include "moveable.h"

class Bullet : public Moveable
{
public:
	Bullet(int x, int y, double dx, double dy, int rotation) : Moveable(x, y, dx, dy, true), movesCounter(0)
	{
		double rotx = cos(deg2rad(rotation)) * 2;
		double roty = sin(deg2rad(rotation)) * 2;
		this->path.setDx(rotx);
		this->path.setDy(roty);
		//std::cout << "Bullet was just created that has a wrap of: " << path.getWrap() << std::endl;
	};
	~Bullet()					{};

	void draw();

	void moveBullet();
	bool readyToDie() { return this->path.isDead(); }

private:
	int movesCounter;
};


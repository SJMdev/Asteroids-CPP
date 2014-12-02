#pragma once

// Abstract class for all items in the game that can move (ie., has a path)

#include "path.h"

class Moveable
{
public:
	Moveable(int x, int y, double dx, double dy, bool wrap) : path()
	{
		path.setX((double)x);
		path.setY((double)y);
		path.setDx(dx);
		path.setDy(dy);

		path.setWrap(wrap);
	};

	~Moveable()							{};

	int getX()							{ return (int)path.getX(); };
	int getY()							{ return (int)path.getY(); };
	double getDX()						{ return path.getDx(); };
	double getDY()						{ return path.getDy(); };

	void setPosition(int x, int y)		{ path.setX((double)x); path.setY((double)y); };
	void setChange(double dx, double dy)	{ path.setDx(dx); path.setDy(dy); };

	virtual void draw() = 0;
	void move()							{ path++; };

protected:
	Path path;

};


#include "Bullet.h"
#include "point.h"
#include <cmath>      // for M_PI, sin() and cos()
#include "uiDraw.h"

#include <iostream>
using namespace std;

// *************************************************************************** 
void Bullet::draw()
{
	drawCircle(path.getPoint(), 2);
}

void Bullet::moveBullet()
{
	if (movesCounter >= 250)
	{
		this->path.kill();
	}
	else
	{
		this->move();
	}
	movesCounter++;
}
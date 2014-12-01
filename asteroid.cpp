#include "Asteroid.h"
#include "point.h"
#include <cmath>      // for M_PI, sin() and cos()
#include "uiDraw.h"

#include <iostream>
using namespace std;

#define Asteroid_RADIUS			10
#define Asteroid_SIDES			3

#define AsteroidLARGE_CIR_RAD	8
#define AsteroidSMALL_CIR_RAD	2

#define MAX_SPEED			12

// *************************************************************************** 
void Asteroid::draw()
{
	drawCircle(path.getPoint(), 8);
}
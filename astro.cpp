#include "astro.h"
#include "uiDraw.h"
#include "asteroid.h"
#include <cmath>

// ************************************************************************
Astro::Astro() : waitCounter(0), nextLaunchAsteroidTime(0)
{
	startGame();
}

// ************************************************************************
Astro::~Astro()
{
	clearAll();
}

// ************************************************************************
void Astro::processFrame(const Interface *pUI)
{
	// Handle UI
	handleUI(pUI);

	//Create asteroids if time permits
	this->determineLuanchAsteroid();

	// Move items
	moveItems();

	determineHitAsteroids();

	// TODO - Handle stuff hitting each other
	//      - detect bullets hitting rocks
	//      - dead bullets

	// Draw stuff
	drawItems();

	this->waitCounter++;
}

double distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void Astro::determineHitAsteroids()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < asteroids.size(); j++)
		{
			if (distance(bullets[i].getX(), bullets[i].getY(), asteroids[i].getX(), asteroids[i].getY()) <= (bullets[i].getRadius() + asteroids[i].getRadius()))
			{
				cout << "HIT!!!!!!!!!!!" << endl;
			}
		}
	}
}

// *************************************************************************** 
void Astro::handleUI(const Interface *pUI) 
{
	if (pUI->isRight())
		ship->rotateRight();

	if (pUI->isLeft())
		ship->rotateLeft();

	if ((pUI->isUp() || pUI->isSpace()) && (pUI->isSpace() % 5 == 0 || pUI->isSpace() == 1))
		shoot();

	if (pUI->isDown())
		rocketBurst();

	// TODO - any other handling of keys
}

// *************************************************************************** 
void Astro::moveItems()
{
	// Ship
	ship->move();

	// Todo - Bullets

	if (!bullets.empty())
	{
		if (bullets[0].readyToDie())
		{
			bullets.erase(bullets.begin());
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].moveBullet();
	}
	

	// Todo - Rocks
	if (!asteroids.empty())
	{
		if (asteroids[0].readyToDie())
		{
			asteroids.erase(asteroids.begin() + 0);
		}
	}
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].move();
	}

	// ToDo - anything else
}

// *************************************************************************** 
void Astro::drawItems()
{
	// Draw Ship
	ship->draw();

	// Todo - Draw Bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].draw();
	}

	// ToDo - Draw Rocks
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].draw();
	}

	// ToDo - any thing else
}

// ************************************************************************
void Astro::clearAll()
{
	// Delete the ship
	delete ship;

	// ToDo - delete anything else
}

// ************************************************************************
void Astro::startGame()
{
	// Clear all current items from the game
	clearAll();

	// Create ship in the centre
	ship = new Ship(0, 0, 0, 0);

	// ToDo - create anything else for the game
}

// *************************************************************************** 
void Astro::shoot()
{
	int x = this->ship->getX();
	int y = this->ship->getY();
	double dx = this->ship->getDX();
	double dy = this->ship->getDY();

	//Randomly set one of the axis to max so that it comes onto the screen
	this->bullets.push_back(Bullet(x, y, dx, dy, this->ship->getRotation()));
}

// *************************************************************************** 
void Astro::rocketBurst()
{
	ship->rocketBurst();
}


void Astro::launchAsteroid()
{
	int x = rand() % (int)Point::xMax + 1;
	int y = rand() % (int)Point::yMax + 1;
	int dxN = 1;
	int dyN = 1;
	//Randomly set one of the axis to max so that it comes onto the screen
	if (x > y)
	{
		x = (int)Point::xMax * pow(-1, (int)(rand() % 2 + 1));
	}
	else
	{
		y = (int)Point::yMax * pow(-1, (int)(rand() % 2 + 1));
	}
	if (x > 0)
	{
		dxN = -1;
	}
	if (y > 0)
	{
		dyN = -1;
	}
	double dy = (rand() % 2 + 1.0) * dyN;
	double dx = (rand() % 2 + 1.0) * dxN;
	this->asteroids.push_back(Asteroid(x, y, dx, dy));
	//cout << "(" << x << "," << y << ") was sent to [" << dx << "," << dy << "]" << endl;
}


void Astro::determineLuanchAsteroid()
{
	if (waitCounter >= nextLaunchAsteroidTime)
	{
		launchAsteroid();
		int randNum = rand() % 100;
		nextLaunchAsteroidTime += randNum;
	}
}
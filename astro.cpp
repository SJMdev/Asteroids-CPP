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

	// TODO - Handle stuff hitting each other
	//      - detect bullets hitting rocks
	//      - dead bullets

	// Draw stuff
	drawItems();

	this->waitCounter++;
}

// *************************************************************************** 
void Astro::handleUI(const Interface *pUI)
{
	if (pUI->isRight())
		ship->rotateRight();

	if (pUI->isLeft())
		ship->rotateLeft();

	if (pUI->isUp() || pUI->isSpace())
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

	// Todo - Rocks
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
   // Todo - Get centre of ship

   // Todo - get rotation of ship

   // create bullet
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
	cout << "(" << x << "," << y << ") was sent to [" << dx << "," << dy << "]" << endl;
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
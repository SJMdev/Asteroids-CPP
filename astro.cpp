#include "astro.h"
#include "uiDraw.h"
#include "asteroid.h"
#include <cmath>

// ************************************************************************
Astro::Astro() : waitCounter(0)
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
	for each(Asteroid asteroid in this->asteroids)
	{
		asteroid.move();
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
	for each(Asteroid asteroid in this->asteroids)
		asteroid.draw();

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
	Asteroid newAsteroid = Asteroid(10, 10, 10, 10);
	this->asteroids.push_back(newAsteroid);
	std::cout << "New asteroid created";
}


void Astro::determineLuanchAsteroid()
{
	if (this->waitCounter % 100 == 0)
	{
		launchAsteroid();
	}
}




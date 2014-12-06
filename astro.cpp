#include "astro.h"
#include "uiDraw.h"
#include "asteroid.h"
#include <cmath>

#define ASTEROID_BIG_RADIUS 10
#define ASTEROID_MEDIUM_RADIUS 6
#define ASTEROID_LITTLE_RADIUS 3


// ************************************************************************
Astro::Astro() : waitCounter(0), nextLaunchAsteroidTime(0), state(IN_PLAY)
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
	//Make a stateful logic statement here that says "if game is in play", "if game is in menu", "if game is over"
	if (state == IN_PLAY)
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
	}
	this->waitCounter++;
}

double distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void Astro::determineHitAsteroids()
{
	//Determine if bullets hit any asteroids
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < asteroids.size(); j++)
		{
			if (distance(bullets[i].getX(), bullets[i].getY(), asteroids[j].getX(), asteroids[j].getY()) <= (bullets[i].getRadius() + asteroids[j].getRadius()))
			{
				//Split up big asteroids
				if (asteroids[j].getRadius() == ASTEROID_BIG_RADIUS)
				{
					launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_MEDIUM_RADIUS);
					launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_MEDIUM_RADIUS);
				}
				else if (asteroids[j].getRadius() == ASTEROID_MEDIUM_RADIUS)
				{
					launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
					launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
					launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
				}
				asteroids.erase(asteroids.begin() + j);
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}

	//Determine if ship is hit or not
	for (int j = 0; j < asteroids.size(); j++)
	{
		if (distance(ship->getX(), ship->getY(), asteroids[j].getX(), asteroids[j].getY()) <= (10 + asteroids[j].getRadius()))
		{
			cout << "GAME OVER";
			state = GAME_OVER;
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
	vector<int> asteroidsToDelete;
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].move();
		if (asteroids[i].readyToDie())
		{
			asteroidsToDelete.push_back(i);
			asteroids[i].getPath().resurrect();
		}
	}

	for (int i = 0; i < asteroidsToDelete.size(); i++)
	{
		asteroids.erase(asteroids.begin() + asteroidsToDelete[i] - i);
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
	static int id;
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
	//Randomly set one of the axis to max so that it comes onto the screen
	if (x > y)
	{
		x = (int)Point::xMax * pow(-1, (int)(rand() % 2 + 1));
	}
	else
	{
		y = (int)Point::yMax * pow(-1, (int)(rand() % 2 + 1));
	}
	launchAsteroid(x, y, ASTEROID_BIG_RADIUS);
}

void Astro::launchAsteroid(double x, double y, int size)
{
	int dxN = 1;
	int dyN = 1;
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
	static int id;
	this->asteroids.push_back(Asteroid(x, y, dx, dy, id++, size, size));
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
#pragma once

#include "ship.h"
#include "asteroid.h"
#include "uiInteract.h"

#include <vector>
using namespace std;

class Astro
{
public:
	Astro();
	~Astro();

	void processFrame(const Interface *pUI);

private:
	Ship			*ship;
	// TODO - another stuff the game has
	vector<Asteroid> asteroids;

	void startGame();

	void clearAll();

	void handleUI(const Interface *pUI);
	void moveItems();
	void drawItems();

	// Ship functions
	void shoot();
	void rocketBurst();
	void launchAsteroid();
	void determineLuanchAsteroid();
	int waitCounter;

	// TODO - Collide function(s)
};


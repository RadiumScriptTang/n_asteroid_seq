#pragma once
#include "pch.h"


#include "Constant.h"
#include <vector>
#include "Star.h"
#include "Asteroid.h"
using namespace std;

class Box
{
private:
	const double gravity = 6.67e-5;
	vector <Star> stars;
	vector <Asteroid> asteroids;
	unsigned seed;
	unsigned iteration;
public:
	//Initial function which create sets of asteroids and planets
	Box(unsigned star, unsigned asteroid, unsigned seed, unsigned iteration);

	//run the iteration
	void run();

	//renew velocity for each asteroid
	void renewVelocity();
	//check whether there is a collison. If so, exchange their velocities according to the rules.
	void checkImpact();


	// functions to write the result
	void writeInit();
	void writeFinal();
};


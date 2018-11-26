#include "pch.h"
#include <cmath>
#include <random>
#include <iostream>
#include <graphics.h>
#include <iomanip>
#include <concrt.h>
#include <fstream>
#include "Box.h"

//step1: create asteroids and step2: create planets
Box::Box(unsigned star, unsigned asteroid, unsigned seed, unsigned iteration)
{
	this->iteration = iteration;
	default_random_engine re{ seed };
	uniform_real_distribution <double> xdist{ 0.0,200.0};
	uniform_real_distribution <double> ydist{ 0.0,200.0};
	normal_distribution <double> mdist{ 1000.0,50.0 };

	for (unsigned i = 0; i < asteroid; i++)
	{
		this->asteroids.push_back(Asteroid(xdist(re), ydist(re), mdist(re)));
	}

	for (unsigned i = 0; i < star; i++)
	{
		switch (i % 4)
		{
		case 0:
			this->stars.push_back(Star(0, ydist(re), mdist(re) * 10));
			break;
		case 1:
			this->stars.push_back(Star(xdist(re), 0, mdist(re) * 10));
			break;
		case 2:
			this->stars.push_back(Star(200, ydist(re), mdist(re) * 10));
			break;
		default:
			this->stars.push_back(Star(xdist(re), 200, mdist(re) * 10));
		}
	}
}


void Box::renewVelocity()
{
	double forceFactor;
	for (unsigned i = 0; i < this->asteroids.size(); i++)
	{
		//step 3.1: Calculate resulting force for each asteroid, 
		//first computing the effect of other asteroids, followed by the force exerted by planets
		for (unsigned j = i + 1; j < this->asteroids.size(); j++)
		{
			forceFactor = Star::calculateForceFactor(this->asteroids[i], this->asteroids[j]);
			double forceX = Star::calculateForceX(forceFactor, this->asteroids[i], this->asteroids[j]);
			double forceY = Star::calculateForceY(forceFactor, this->asteroids[i], this->asteroids[j]);

			double accelerationX = forceX / this->asteroids[i].getMass();
			double accelerationY = forceY / this->asteroids[i].getMass();
			this->asteroids[i].setVelocityX(accelerationX * TI);
			this->asteroids[i].setVelocityY(accelerationY * TI);

			accelerationX = -forceX / this->asteroids[j].getMass();
			accelerationY = -forceY / this->asteroids[j].getMass();
			this->asteroids[j].setVelocityX(accelerationX * TI);
			this->asteroids[j].setVelocityY(accelerationY * TI);

		}

		for (auto planet : this->stars)
		{
			forceFactor = Star::calculateForceFactor(this->asteroids[i], planet);
			double forceX = Star::calculateForceX(forceFactor, planet, this->asteroids[i]);
			double forceY = Star::calculateForceY(forceFactor, planet, this->asteroids[i]);
			double accelerationX = forceX / this->asteroids[i].getMass();
			double accelerationY = forceY / this->asteroids[i].getMass();
			this->asteroids[i].setVelocityX(accelerationX * TI);
			this->asteroids[i].setVelocityY(accelerationY * TI);
		}

	}
	// to be contimued
	// test the velocity:
}

void Box::checkImpact()
{
	for (unsigned i = 0; i < this->asteroids.size(); i++)
	{
		for (unsigned j = i + 1; j < this->asteroids.size(); j++)
		{
			double distance = Star::calculateDistanceSquare(this->asteroids[i], this->asteroids[j]);
			if (distance <= 4)
			{
				Asteroid::swapVelocity(this->asteroids[i], this->asteroids[j]);
			}
		}
	}
}

void Box::run()
{
	for (unsigned i = 0; i < this->iteration; i++)
	{
		//step 3.1
		this->renewVelocity();
		//step 3.2
		for (unsigned j = 0; j < this->asteroids.size(); j++)
		{
			this->asteroids[j].move();
		}

		//step 3.3

		for (unsigned j = 0; j < this->asteroids.size(); j++)
		{
			this->asteroids[j].checkBorder();
		}
		//step 3.4
		this->checkImpact();
	}
}





void Box::writeInit()
{
	ofstream init("init.txt");
	init << "==============planets==============" << endl;
	init << "#" << '\t' << "positonX" << '\t' << "positionY" << '\t' << "mass" << endl;
	for (unsigned i = 0; i < this->stars.size(); i++)
	{
		init << i << '\t' << setiosflags(ios::fixed) << setprecision(3) << this->stars[i].getPositionX()
			<< '\t' << this->stars[i].getPositionY() << '\t' << this->stars[i].getMass() << endl;
	}

	init << "==============asteroids==============" << endl;
	init << "#" << '\t' << "positonX" << '\t' << "positionY" << '\t' << "mass" << endl;
	for (unsigned i = 0; i < this->asteroids.size(); i++)
	{
		init << i << '\t' << setiosflags(ios::fixed) << setprecision(3) << this->asteroids[i].getPositionX()
			<< '\t' << this->asteroids[i].getPositionY() << '\t' << this->asteroids[i].getMass() << endl;
	}
}

void Box::writeFinal()
{
	ofstream out("out.txt");

	out << "==============asteroids==============" << endl;
	out << "#" << '\t' << "positonX" << '\t' << "positionY" << '\t' << "Vx" << '\t' << "Vy" << '\t' << "mass" << endl;
	for (unsigned i = 0; i < this->asteroids.size(); i++)
	{
		out << i << '\t' << setiosflags(ios::fixed) << setprecision(3) 
			<< this->asteroids[i].getPositionX()
			<< '\t' << this->asteroids[i].getPositionY() << '\t'
			<< this->asteroids[i].getVelocityX() << '\t'
			<< this->asteroids[i].getPositionY() << '\t'
			<< this->asteroids[i].getMass() << endl;
	}
}

#include "pch.h"
#include "Star.h"
#include <cmath>
#include "Constant.h"

Star::Star(double x, double y, double mass)
{
	this->positionX = x;
	this->positionY = y;
	this->mass = mass;
}
void Star::setPositionX(double x)
{
	this->positionX = x;
}

void Star::setPositionY(double y)
{
	this->positionY = y;
}

double Star::getPositionX()
{
	return this->positionX;
}

double Star::getPositionY()
{
	return this->positionY;
}

double Star::getMass()
{
	return this->mass;
}

double Star::calculateDistanceSquare(Star starA, Star starB)
{
	return pow(starA.positionX - starB.positionX, 2)
		+ pow(starA.positionY - starB.positionY, 2);
}

double Star::calculateForceFactor(Star starA, Star starB)
{
	if (calculateDistanceSquare(starA, starB) <= 4)
		return GRAVITY * starA.mass * starB.mass / 8;
	return GRAVITY * starA.mass * starB.mass / pow(sqrt(calculateDistanceSquare(starA, starB)), 3);
}

double Star::calculateForceX(double forceFactor, Star starA, Star starB)
{
	return forceFactor * (starA.positionX - starB.positionX);
}

double Star::calculateForceY(double forceFactor, Star starA, Star starB)
{
	return forceFactor * (starA.positionY - starB.positionY);
}
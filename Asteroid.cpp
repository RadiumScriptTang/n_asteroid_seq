#include "pch.h"
#include "Star.h"
#include "Asteroid.h"

Asteroid::Asteroid(double x, double y, double mass) :
	Star(x, y, mass)
{
	this->velocityX = 0;
	this->velocityY = 0;
}

void Asteroid::setVelocityX(double vx)
{
	this->velocityX += vx;
}

void Asteroid::setVelocityY(double vy)
{
	this->velocityY += vy;
}

void Asteroid::swapVelocity(Asteroid a, Asteroid b)
{
	double tempVx = a.velocityX;
	double tempVy = a.velocityY;
	a.velocityX = b.velocityX;
	a.velocityY = b.velocityY;
	b.velocityX = tempVx;
	b.velocityY = tempVy;
}

double Asteroid::getVelocityX()
{
	return this->velocityX;
}

double Asteroid::getVelocityY()
{
	return this->velocityY;
}

void Asteroid::checkBorder()
{
	if (this->positionX <= 0)
	{
		this->setPositionX(DMIN);
	}
	else if (this->positionX >= WIDTH)
	{
		this->setPositionX(WIDTH - DMIN);
	}

	if (this->positionY <= 0)
	{
		this->setPositionY(DMIN);
	}
	else if (this->positionY >= HEIGHT)
	{
		this->setPositionY(HEIGHT - DMIN);
	}
}

void Asteroid::move()
{
	this->positionX += velocityX * TI;
	this->positionY += velocityY * TI;
}


#pragma once
#include "pch.h"


#include "Star.h"

class Asteroid : public Star
{
private:
	double velocityX;
	double velocityY;
public:

	Asteroid(double x, double y, double mass);

	void setVelocityX(double vx);
	void setVelocityY(double vy);
	void move();

	double getVelocityX();
	double getVelocityY();

	void checkBorder();
	static void swapVelocity(Asteroid a, Asteroid b);

};



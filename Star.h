#pragma once
#include "pch.h"


#include "Constant.h"

class Star
{
protected:
	double positionX;
	double positionY;
	double mass;
public:
	void setPositionX(double x);
	void setPositionY(double y);
	double getPositionX();
	double getPositionY();
	double getMass();
	Star(double x, double y, double mass);

	//caclute the square of distance between two stars
	static double calculateDistanceSquare(Star starA, Star starB);
	//calculate the force factor between two stars
	static double calculateForceFactor(Star starA, Star starB);
	//calculate the force between two stars on the OX direction
	static double calculateForceX(double forceFactor, Star starA, Star starB);
	//calculate the force between two stars on the OY direciton
	static double calculateForceY(double forceFactor, Star starA, Star starB);
};


//

#include "pch.h"
#include <iostream>
#include "Box.h"
#include <graphics.h>
#include <concrt.h>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

bool checkParametersNumber(int numberOfParameters) {
	if (numberOfParameters != 5) {
		cerr << "nasteroids-seq: Wrong arguments.\nCorrect use:\n"
			<< "nasteroids-seq num_asteroids num_iterations num_planets seed" << endl;
		return false;
	}
	return true;
}

/**
 * This function checks expected integer arguments
 * @param arg char const* argument integer value
 * @return integer value, exits with error code -1 if error
 */
int checkInteger(char const *arg) {
	try {
		if (stoi(arg) < 0) {
			cerr << "nasteroids-seq: Wrong arguments.\nCorrect use:\n"
				<< "nnasteroids-seq num_asteroids num_iterations num_planets seed" << endl;
			exit(-1);
		}
		return stoi(arg);
	}
	catch (...) {
		cerr << "nasteroids-seq: Wrong arguments.\nCorrect use:\n"
			<< "nasteroids-seq num_asteroids num_iterations num_planets seed" << endl;
		exit(-1);
	}
}


double checkDouble(char const *arg) {
	try {
		if (stod(arg) < 0 || stod(arg) > WIDTH) {
			cerr << "nasteroids-seq: Wrong arguments.\nCorrect use:\n"
				<< "nasteroids-seq num_asteroids num_iterations num_planets seed" << endl;
			exit(-1);
		}
		return stod(arg);
	}
	catch (...) {
		cerr << "nasteroids-seq: Wrong arguments.\nCorrect use:\n"
			<< "nasteroids-seq num_asteroids num_iterations num_planets seed" << endl;
		exit(-1);
	}
}


int main(int argc, char* argv[])
{
	if (!checkParametersNumber(argc)) {
		return -1;
	}
	const int num_asteroids = checkInteger(argv[1]);
	const int num_iterations = checkInteger(argv[2]);
	const int num_planets = checkInteger(argv[3]);
	const auto seed = (unsigned int)checkInteger(argv[4]);

	Box b(num_planets, num_asteroids, seed, num_iterations);
	b.writeInit();
	time_t start_t = clock();
	b.run();
	time_t end_t = clock();
	cout << "time consumed:" << end_t - start_t << "miniseconds" << endl;
	b.writeFinal();
	getchar();
}



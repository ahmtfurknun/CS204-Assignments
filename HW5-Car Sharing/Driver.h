/****************************
* Created by Ahmet Furkan Un*
* 6.12.2021                 *
****************************/

#ifndef DRIVER_H
#define DRIVER_H
#include "Car.h"
using namespace std;


class Driver
{
private:
	double budget;
	Car &shared_car;
public:
	//Constructor
	Driver(Car&, double);

	//Member Functions
	void drive (int);
	void repairCar(string);
	void display();
	void fullFuel();
};
#endif
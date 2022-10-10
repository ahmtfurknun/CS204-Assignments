/****************************
* Created by Ahmet Furkan Un*
* 6.12.2021                 *
****************************/

#include <iostream>
#include <string>
#include "Driver.h"
#include "Car.h"
using namespace std;

Driver::Driver(Car & car, double Budget)
 : shared_car(car), budget(Budget)
{}

void Driver::drive(int distance)
{
	shared_car.increase_distance( distance);
	shared_car.set_fuel( shared_car.get_fuel() - (distance * 0.25));
}

void Driver::repairCar(string accidentType)
{
	if (accidentType == "SMALL")
	{
		budget = budget-50;
		shared_car.multiply_insurance(1.05);
		cout << "50$ is reduced from the driver's budget because of the SMALL accident"<<endl
			<<"Yearly insurance fee is increased to "
			<<shared_car.get_insurance()<<" because of the SMALL accident" << endl;
	}

	else if (accidentType == "MEDIUM")
	{
		budget = budget-150;
		shared_car.multiply_insurance(1.1);
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident"<<endl
			<<"Yearly insurance fee is increased to "
			<<shared_car.get_insurance()<<" because of the MEDIUM accident" << endl;
	}

	else if (accidentType == "LARGE")
	{
		budget = budget - 300;
		shared_car.multiply_insurance(1.2);
		cout << "300$ is reduced from the driver's budget because of the LARGE accident"<<endl
			<<"Yearly insurance fee is increased to "
			<<shared_car.get_insurance()<<" because of the LARGE accident" << endl;
	}
}

void Driver::display()
{
	cout << "Driver Budget: "<<budget<<endl;
}

 void Driver::fullFuel()
 {
	 double fuel_cost = shared_car.get_max_fuel()- shared_car.get_fuel();
	 shared_car.set_fuel(shared_car.get_max_fuel());
	 budget -= fuel_cost;
	 cout << "Fuel is full"<<endl;
 }
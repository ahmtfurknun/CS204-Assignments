/****************************
* Created by Ahmet Furkan Un*
* 6.12.2021                 *
****************************/

#include <iostream>
#include "Car.h"
using namespace std;


Car::Car(double Fuel, double Insurance_fee, int Total_distance)
{
	max_fuel = Fuel;
	fuel = Fuel;
	insurance_fee = Insurance_fee;
	total_distance = Total_distance;
}

void Car::display()
{
	cout<< "Fuel Level: "<< fuel<<endl
		<< "Insurance Fee: "<< insurance_fee<<endl
		<<"Total distance that the car has travelled: "<< total_distance<<endl;
}

void Car::set_fuel(double new_fuel)
{
	fuel = new_fuel;
}
double Car::get_fuel()
{
	return fuel;
}

double Car::get_max_fuel()
{
	return max_fuel;
}

void Car::multiply_insurance(double rate)
{
	insurance_fee = insurance_fee*rate;
}

double Car::get_insurance()
{
	return insurance_fee;
}

void Car::increase_distance(int distance)
{
	total_distance += distance;
}

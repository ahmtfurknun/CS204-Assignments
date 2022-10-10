/****************************
* Created by Ahmet Furkan Un*
* 6.12.2021                 *
****************************/

#ifndef CAR_H
#define CAR_H


class Car
{
private:
	double max_fuel;
	double fuel;
	double insurance_fee;
	int total_distance;
public:
	//Constructor
	
	Car(double, double, int);

	//Member Functions
	void display();
	void set_fuel(double);
	double get_fuel();
	double get_max_fuel();
	void multiply_insurance(double);
	double get_insurance();
	void increase_distance(int);
};
#endif
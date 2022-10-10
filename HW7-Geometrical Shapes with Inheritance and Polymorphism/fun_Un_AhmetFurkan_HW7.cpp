/*****************************
** CS204 HW7                 *
** 09.07.2022                *
** Edited by Ahmet Furkan Un *
** Student ID	: 28315      *
** SU-Net ID	: fun		 *
*****************************/



#include <iostream>
#include <string>
using namespace std;

//abstract class shape
class shape
{
public:
	//constructor
	shape(string name = ""): myName(name){}

	//destructor
	virtual ~shape() {};

	//purely virtual member functions
	virtual float perimeter() = 0;
	virtual float area() = 0;
	virtual float volume() = 0;

	//member function
	virtual string getName()
	{
		return myName;
	}
protected:
	string myName;
};

//abstract class TwoDShape
//inherited from shape class
class TwoDShape : public shape
{
public:
	//contructor
	TwoDShape(string name = ""): shape(name){}

	//destructor
	virtual ~TwoDShape() {}

	//purely virtual member functions
	virtual float perimeter() = 0;
	virtual float area() = 0;

	//member function
	float volume(){return 0;}
};

//abstract class ThreeDShape
//inherited from shape class
class ThreeDShape : public shape
{
public:
	//contructor
	ThreeDShape(string name = ""): shape(name) {}
	
	//destructor
	virtual ~ThreeDShape() {}

	//purely virtual member functions
	virtual float area() = 0;
	virtual float volume() = 0;

	//member function
	float perimeter(){return 0;}
};

//inherited from TwoDShape class
class rectangle : public TwoDShape
{
public:
	//constructor
	rectangle(string name, float len, float wid)
		: TwoDShape(name), length(len), width(wid) {}
	
	//destructor
	virtual ~rectangle(){}

	//member functions
	virtual float area() {return width*length;}
	virtual float perimeter() {return  2*(width + length);}
private:
	float width, length;
};

//inherited from ThreeDShape class
class box : public ThreeDShape
{
public:
	//constructor
	box(string name, float len, float wid, float hei)
		: ThreeDShape(name), length(len), width(wid), height(hei){}
	
	//destructor
	virtual ~box(){}

	//member functions
	virtual float area() {return 2*(width*length+width*height+length*height);}
	virtual float volume() {return  width*length*height;}
private:
	float width, length, height;
};

shape* getShape() 
{
	//initializations
	string choice;
	string name;
	float wid, len, hei;
	shape* ptr;

	//get the option for the shape
	cout << "\nChoose an option (1 or 2):"<<endl;
	cout << "1. Rectangle"<< endl; 
	cout << "2. Box"<< endl;
	cin >> choice;
	while(choice != "1" && choice != "2")
	{
		cout << "UNAVAILABLE OPTION CHOOSEN. Try again."<<endl;
		cout << "\nChoose an option (1 or 2):"<<endl;
		cout << "1. Rectangle"<< endl; 
		cout << "2. Box"<< endl;
		cin >> choice;
	}
	if(choice == "1")
	{
		cout << "You chose rectangle. Give it's width, length and name:" <<endl;
		cin >> wid >> len >> name;

		//create new rectangle object, which is pointed by ptr
		ptr = new rectangle (name, len, wid);
	}

	else if(choice == "2")
	{
		cout << "You chose box. Give it's width, length, height and name:" <<endl;
		cin >> wid >> len >> hei>>name;

		//create new box object, which is pointed by ptr
		ptr = new box (name, len, wid, hei);
	}
	return ptr;
}//getShape()



int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}
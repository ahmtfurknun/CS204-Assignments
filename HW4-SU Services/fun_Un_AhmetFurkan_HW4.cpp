/*****************************
* CS204 HW3                  *
* 28.11.2021                 *
* Created by Ahmet Furkan Un *
* Student ID	: 28315      *
* SU-Net ID		: fun        *
*****************************/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "IntQueue.h"
#include "DynIntStack.h"
#include "DynIntQueue.h"

using namespace std;


#include "windows.h" 
#define _CRTDBG_MAP_ALLOC //to get more details 
#include <stdlib.h>   
#include <crtdbg.h>

struct commandNode
/*This struct will be used to store commands in linked list*/
{
	string command, value;
	commandNode* next;

	/*constructor*/
	commandNode(string Command, string value_of_command)
	{
		command = Command;
		value = value_of_command;
		next = NULL;
	}
};

struct functionNode
/*This struct will be used to store functions in linked list*/
{
	string function_name;
	functionNode* next;
	commandNode* commands;

	/*Constructor*/
	functionNode(string name, functionNode* next_function, commandNode* commandsHead)
	{
		function_name=name;
		next = next_function;
		commands = commandsHead;
	}
};


/*Construction of stack, linked list and queues*/
functionNode* head = NULL;
IntQueue instructorsQueue(5);
DynIntQueue studentsQueue;
DynIntStack requests;

/*Prototypes of the funcitons*/
void menu();
void addInstructorRequest();
void addStudentRequest();
void delete_colon(string & functionName);
void AddFunction(functionNode * new_node);
commandNode* AddCommand(commandNode * command_head, commandNode * new_node);
void printList();
functionNode* find_function(string function_name);
void print_stack(DynIntStack& stack);
void deleteFunctionFromStack(DynIntStack& stack, string function_name);
void processARequest(string functionName);
void processARequest();
void delete_list();

int main()
{
	_CrtMemState sOld; 
    _CrtMemState sNew; 
    _CrtMemState sDiff; 
    _CrtMemCheckpoint(&sOld);



	string choice, filename;
	cout <<"If you want to open a service (function) defining file"<<endl
		<<"then press (Y/y) for \'yes\', otherwise press any single key"<<endl;
	cin >> choice;
	if(choice == "Y" || choice == "y")
	{
		/*While user keeps typing Y, get the filename and open it*/
		while (choice == "Y" || choice == "y")
		{
			ifstream input;
			cout<<"Enter the input file name: ";
			cin >>filename;
			input.open(filename.c_str());

			/*if could not open the given filename
			display the message and exit the program*/
			if (input.fail())
			{
				cout <<"Error, couldn't open the file "<< filename<<"!"<< endl;
				cout<<"PROGRAM EXITING ... "<<endl; 
				system("pause"); 
				_CrtMemCheckpoint(&sNew); //take a snapchot  
				if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference 
				{ 
					OutputDebugString(L"-----------_CrtMemDumpStatistics ---------"); 
					_CrtMemDumpStatistics(&sDiff); 
					OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------"); 
					_CrtMemDumpAllObjectsSince(&sOld); 
					OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------"); 
					_CrtDumpMemoryLeaks(); 
				} 
				exit(0);
			}

			/*if program opens the given filename correctly*/
			else
			{
				string input_line, function_name;

				/*Get the function name on the top of the file*/
				getline(input, function_name);
				delete_colon(function_name);

				/*create a linked list to store the commands of the current function*/
				commandNode* commands = NULL;

				/*go over the file and get the commands*/
				while (getline(input, input_line)&& input_line.size() >0)
				{
					string command, value;
					istringstream input_line_stream(input_line);
					input_line_stream >> command>>value;
					delete_colon(value);

					/*add the current command to the commands linked list*/
					commands = AddCommand(commands, new commandNode(command, value));
				}

				/*Add the function from current file to the main linked list*/
				AddFunction(new functionNode(function_name, NULL, commands));

				cout << "Do you want to open another service defining file?"<<endl
					<<"Press (Y/y) for \'yes\', otherwise press anykey"<<endl;
				cin >> choice;
			}
			input.clear();//in order to open another file
		}
		cout <<"-------------------------------------------------------------------"<<endl
			 <<"PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS"<<endl
			 <<"-------------------------------------------------------------------"<<endl;
		printList();
		menu();
	}

	else
	{
		cout<<"PROGRAM EXITING ... "<<endl;
	}



	return 0;
}


void menu()
{
	while (true)
	{ 
		cout << endl; 
		cout<<"**********************************************************************"<<endl 
			<<"**************** 0 - EXIT PROGRAM *************"<<endl 
			<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl 
			<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl 
			<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl 
			<<"**********************************************************************"<<endl;
		cout << endl; 
		int option; 
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option; 
		switch (option) 
		{ 
			case 0: 
				cout<<"PROGRAM EXITING ... "<<endl; 
				delete_list();
				system("pause"); 
				exit(0); 
			case 1: 
				addInstructorRequest(); 
				break; 
			case 2: 
				addStudentRequest(); 
				break; 
			case 3: 
				processARequest();
				break; 
			default: 
				cout<<"INVALID OPTION!!! Try again"<<endl; 
		}//switch 
	}//while (true)
}

void processARequest(string functionName)
{
	/*find the addres of the funciton with given name and find the addres of the head of commands*/
	commandNode* ptr = find_function(functionName)->commands;

	/*go throug the commands of the current function*/
	while (ptr != NULL)
	{
		if( ptr->command =="define")
		{
			/*add this command to the shared stack*/
			requests.push(StackNode(ptr->command, ptr->value, functionName));
		}

		else if (ptr->command=="call")
		{
			// the recursion goes here
			cout<< "Calling "<<ptr->value<<" from "<< functionName<<endl;
			processARequest(ptr->value);
		}
		else
		{
			//print the stack …
			print_stack(requests);
		}	
		ptr = ptr->next;
	}// while
	//…
	// delete this function’s data from the top of the stack
	deleteFunctionFromStack(requests, functionName);
	cout<<functionName<<" is finished. Clearing the stack from it's data... "
					<<endl;
	system("pause");
	if(requests.isEmpty())
	{
		cout << "The stack is empty."<<endl;
	}
}

void processARequest()
{
	if (!instructorsQueue.isEmpty())
	{
		//if instructors queue is not empty, process the next request

		/*get the request that have priority*/
		QueueNode temp;
		instructorsQueue.dequeue(temp);

		cout<<"Proccessing instructors queue..."<<endl;
		cout<<"Processing Prof. "<<temp.name <<"\'s request (with ID "<<temp.id<<") of service (function):"<<endl
			<<temp.function_name<<endl;
		cout<<"------------------------------------------------------------------------------------" <<endl;
		processARequest(temp.function_name);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentsQueue.isEmpty())
	{
		//…
		 //if instructors queue is empty and student’s not,
		 //then process the next student request
		DynQueueNode temp;
		studentsQueue.dequeue(temp);
		cout<<"Instructors queue is empty. Procceding with students queue..."<<endl;
		cout<<"Processing "<<temp.name <<"\'s request (with ID "<<temp.id<<") of service (function):"<<endl
			<<temp.function_name<<endl;
		cout<<"------------------------------------------------------------------------------------" <<endl;
		processARequest(temp.function_name);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else
	{
		// otherwise…
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl
			<<"GOING BACK TO MAIN MENU"<<endl;
	}
}

void addInstructorRequest()
{
	/*get the function name from the user*/
	string function_name;
	cout << "Add a service (function) that the instructor wants to use: "<<endl;
	cin >> function_name;

	/*if the function does not exist*/
	if (find_function(function_name) == NULL)
	{
		cout<<"The requested service (function) does not exist."<<endl
			<<"GOING BACK TO MAIN MENU"<<endl;
	}

	/*if the function exists*/
	else
	{
		/*get the information of the request*/
		string name;
		int id;
		cout << "Give instructor\'s name: ";
		cin >>name;
		cout << "Give instructor\'s ID (an int): ";
		cin >> id;

		/*add request to the queue*/
		instructorsQueue.enqueue(QueueNode (function_name, name, id));

		cout << "Prof. "<<name<<"\'s service request of "<< function_name<<" has been put in the istructor\'s queue."<<endl
			<<"Waiting to be served..."<<endl;
	}
}

void addStudentRequest()
{
	/*get the function name from the user*/
	string function_name;
	cout << "Add a service (function) that the student wants to use: "<<endl;
	cin >> function_name;

	/*if the function does not exist*/
	if (find_function(function_name) == NULL)
	{
		cout<<"The requested service (function) does not exist."<<endl
			<<"GOING BACK TO MAIN MENU"<<endl;
	}

	/*if the function exists*/
	else
	{
		/*get the information of the request*/
		string name;
		int id;
		cout << "Give student\'s name: ";
		cin >>name;
		cout << "Give student\'s ID (an int): ";
		cin >> id;

		/*add request to the queue*/
		studentsQueue.enqueue(DynQueueNode (function_name, name, id));

		cout <<name<<"\'s service request of "<< function_name<<" has been put in the student\'s queue."<<endl
			<<"Waiting to be served..."<<endl;
	}
}

void delete_colon(string & functionName)
/*This function creates the substring of the given string to get rid of the last character
from index 0 to index (size-2)*/
{
	string result = "";
	for(int i = 0; i< functionName.size()-1; i++)
	{
		result += functionName[i];
	}

	functionName=result;
}

void AddFunction(functionNode * new_node)
//pre: given a linked list
//post: add the new node to the end of the list
/*taken from lecture slides and modified by Ahmet Furkan Un*/
{
   functionNode *  ptr = head;   // loop variable

   // if the list is empty and new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
    if (head == NULL)        
    {   
		new_node->next = head;
		head = new_node;
    }

	else
	{
		// go to the last node
		while (ptr->next != NULL)
		{    
			ptr = ptr->next;
		} 

		//now insert new node after where ptr points to
		new_node->next = ptr->next;
		ptr->next = new_node;
	}
}

commandNode * AddCommand(commandNode * command_head, commandNode * new_node)
//pre: given a head of a linked list and the address of the new node
//post: add the new node to the end of the list
/*taken from lecture slides and modified by Ahmet Furkan Un*/
{
   commandNode *  ptr = command_head;   // loop variable

   // if the list is empty and new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
    if (command_head == NULL)        
    {   
		new_node->next = command_head;
		return new_node;
    }

    // go to the last node
    while (ptr->next != NULL)
    {    
		ptr = ptr->next;
    } 

    //now insert new node after where ptr points to
	new_node->next = ptr->next;
	ptr->next = new_node;
	return command_head;
}

void printList()
//post: prints the information of the linked list namely global head.
{
	functionNode* ptrF = head; // loop variable for functions
	while(ptrF != NULL)
	{
		cout << ptrF->function_name<<": "<<endl;
		
		commandNode* ptrC = ptrF->commands; // loop variable for functions
		while(ptrC != NULL)
		{
			cout << ptrC->command << " "<< ptrC->value ;

			/*if it is the last command, print "." at the end*/
			if(ptrC->next == NULL)
			{
				cout << "."<< endl;
			}

			/*if it is not the last command, print "," between commands*/
			else
			{
				cout << ", ";
			}
			ptrC=ptrC->next;
		}
		ptrF = ptrF->next;
		cout << endl;
	}
}

functionNode* find_function(string function_name)
//pre: given a string (the name of the function)
//post: if the given function exists, returns the address of the function
//		else returns NULL
{
	functionNode* ptr = head;
	while (ptr != NULL && ptr->function_name != function_name)
	{
		ptr = ptr->next;
	}

	/*if could not find the function, ptr will point to the end of the list which is NULL*/
	return ptr;
}

void print_stack(DynIntStack& stack)
{
	StackNode temp;
	DynIntStack helper;
	cout<<"PRINTING THE STACK TRACE:"<<endl;

	if(stack.isEmpty())
	{
		cout << "The stack is empty"<<endl;
	}

	else
	{
		/*pop the elements of the stack and push them to the helper*/
		while( !stack.isEmpty())
		{
			stack.pop(temp);
			helper.push(temp);
		}

		/*pop the elements of the helper and push them to the stack again*/
		/*while pushing, display the elements*/
		while( !helper.isEmpty())
		{
			helper.pop(temp);
			stack.push(temp);
			cout << temp.function_name <<": "<<temp.command<<" "<<temp.value<<endl;
		}
	}
}

void deleteFunctionFromStack(DynIntStack& stack, string function_name)
//pre: given a reference stack and a function name
//post: removes the elements that have given function name from the stack
//      if the elements are at the top
{
	StackNode temp;
	bool is_deleted = false; 

	while( !is_deleted)
	{
		stack.pop(temp);

		/*if stack is empty than the deletion must occured before*/
		if(stack.isEmpty())
		{
			is_deleted = true;
		}

		/*if the current function name is different than the given function, the deletion is done*/
		else if(temp.function_name != function_name && temp.function_name != "")
		{
			is_deleted = true;

			/*push the last one back to the stack*/
			stack.push(temp);
		}
	}
}

void delete_list()
//post: deletes the dynamically allocated linked list in order to prevent memory leaks
{
	functionNode* ptr = NULL; 
	while( head != NULL)
	{
		ptr=head->next;
		commandNode* ptrC = NULL;
		while( ptr != NULL && ptr->commands != NULL)
		{
			ptrC=ptr->commands->next;
			delete ptr->commands;
			ptr->commands = ptrC;
		}
		delete head;
		head = ptr;
	}
}
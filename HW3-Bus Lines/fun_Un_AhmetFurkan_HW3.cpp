/*****************************
* CS204 HW3                  *
* 17.11.2021                 *
* Created by Ahmet Furkan Un *
* Student ID	: 28315      *
* SU-Net ID		: fun        *
*****************************/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct busStop 
{
	string busStopName;
	busStop *left;
	busStop *right;

	busStop(string bus_stop_name, busStop* left_bus_stop, busStop* right_bus_stop)
	{
		busStopName = bus_stop_name;
		left = left_bus_stop;
		right = right_bus_stop;
	}
};

struct busLine 
{
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine(string bus_line_name, busLine* next_bus_line, busStop* bus_stops)
	{
		busLineName = bus_line_name;
		next = next_bus_line;
		busStops = bus_stops;
	}
};

busLine* head = nullptr;

void printMainMenu();
bool consistencyCheck(); 
void printBusLines(busLine* head);
void print_one_bus_line(string bus_line_name);
void print_between_two_stops(busLine* bus_line, string start_name, string finish_name);
busLine* add_bus_line_to_end_of_list(busLine* new_line);
busLine* add_bus_line_to_beggining_of_list(busLine* new_line);
busStop* add_bus_stop_to_end_of_list(busStop* head, busStop* new_stop);
busStop* add_bus_stop_to_beginning_of_list(busStop* head, busStop* new_stop);
busStop* add_bus_stop_after_the_given_stop(busStop* head, busStop* new_stop, string previous_bus_stop);
busLine* find_bus_line(string line_to_find);
busStop* find_bus_stop(busStop* head, string stop_to_find);
void delete_lineandstops_of_bus_line(busLine* address_of_line);
void delete_colon(string & busLine_name);
busLine* delete_line(busLine* address_of_line);
busStop* delete_stop(busStop* head_stops, string name_of_stop);
bool are_two_stops_in_the_line(busLine* bus_line, string stop_1, string stop_2);

void addBusLine();
void addBusStop();
void deleteBusLine();
void deleteBusStop();
void pathfinder();
void processMainMenu(); 


int main()
{
	/*open file*/
	string filename = "busLines.txt";
	ifstream input;
	input.open(filename.c_str());
	if (input.fail())
	{
		cout <<"Error, couldn't open the file"<< filename<<"!"<< endl;
	}
	else
	{
		/*get data from the file*/
		string input_line;
		while (getline(input, input_line)&& input_line.size() >0)
		{
			string busLine_name, busStop_name;
			istringstream input_line_stream(input_line);

			/*get the bus line name for this particular line of the file*/
			input_line_stream >> busLine_name;

			/*get rid of the ":" at the end of the line name*/
			delete_colon(busLine_name);

			/*initialize the linked list for the bus stops*/
			busStop* bus_stops_head = nullptr;

			/*repeatedly an one by one get the bus stops*/
			while(input_line_stream >> busStop_name)
			{
				/*add bus stop to to linked list*/
				bus_stops_head = add_bus_stop_to_end_of_list(bus_stops_head, new busStop(busStop_name, nullptr, nullptr));
			}

			/*add the bus line with the stops to the main linked list*/
			head = add_bus_line_to_end_of_list(new busLine(busLine_name, nullptr, bus_stops_head));
		}
	}
	cout<< "Execution:\n";
	processMainMenu();

	/*free the dynamically allocated memory*/
	busLine* ptr = head;
	while(ptr != nullptr)
	{
		ptr = head->next;
		delete_lineandstops_of_bus_line(head);
		head = ptr;
	}
	return 0;
}


void printMainMenu() 
{
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

bool consistencyCheck() 
{
	busLine* currBL = head; //a global variable
	while(currBL) 
	{
		busStop* currBS = currBL->busStops;
		while(currBS) 
		{
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) 
			{
				cout << "Inconsistency for " << currBL->busLineName
					 << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

void printBusLines(busLine* head)
/*This function display all the bus lines and bus stops*/
{
	/*loop pointer*/
	busLine* ptr = head;

	/*go through the bus lines*/
	while(ptr != nullptr )
	{
		/*display the bus line name*/
		cout << ptr->busLineName<< ": ";

		/*loop pointer for the bus stops*/
		busStop* ptr_busstop = ptr->busStops;

		/*go through the stops*/
		while(ptr_busstop != nullptr )
		{

			/*display the first stop to handle with "<->" between stops*/
			if (ptr_busstop == ptr->busStops)
			{
				cout << ptr_busstop->busStopName;
			}

			/*other than first stop, display " <-> BusStop*/
			else
			{
				cout << " <-> "<<ptr_busstop->busStopName;
			}

			/*go to next stop*/
			ptr_busstop = ptr_busstop->right;
		}

		/*newline between each bus line*/
		cout << endl;

		/*go to next bus line*/
		ptr = ptr->next;
	}
}

void print_one_bus_line(string bus_line_name)
/*This function gets the name of the line and displays the stops of it*/
{
	cout <<bus_line_name << ": ";

	/*initialize the loop pointer*/
	busStop* ptr_busstop = find_bus_line(bus_line_name)->busStops;

	/*go through the stops*/
	while(ptr_busstop != nullptr )
	{

		/*display the stops with " <-> " between each other*/
		if (ptr_busstop == find_bus_line(bus_line_name)->busStops)
		{
			cout << ptr_busstop->busStopName;
		}
		else
		{
			cout << " <-> "<<ptr_busstop->busStopName;
		}

		/*go to next stop*/
		ptr_busstop = ptr_busstop->right;
	}
}

void print_between_two_stops(busLine* bus_line, string start_name, string finish_name)
/*This function gets the pointer to the bus line and names of 2 stops
Displays the stops between these two stops*/
{
	/*initialize name of the line and two pointers to the stops*/
	string bus_line_name = bus_line->busLineName;
	busStop* start = find_bus_stop(bus_line->busStops, start_name);
	busStop* finish = find_bus_stop(bus_line->busStops, finish_name);

	/*initialize the boolean variable*/
	bool is_start_before_finish = false;
	
	/*start from the first bus and go throug the stops
	check whether the first stop is coming before*/
	busStop* ptr = start;
	while(ptr != nullptr)
	{
		if(ptr == finish)
		{
			is_start_before_finish = true;
		}
		ptr=ptr->right;
	}

	/*if start is before the finish, go to the Right direction*/
	if(is_start_before_finish)
	{
		cout<< bus_line_name << ": "<< start->busStopName;
		ptr = start->right;
		while(ptr != finish->right)
		{
			cout << " -> "<< ptr->busStopName;
			ptr = ptr->right;
		}
	}

	/*if finish comes before, go throug the reverse direction*/
	else
	{
		cout<< bus_line_name << ": "<< start->busStopName;
		ptr = start->left;
		while(ptr != finish->left)
		{
			cout << " -> "<< ptr->busStopName;
			ptr = ptr->left;
		}
	}
}

busLine* add_bus_line_to_end_of_list(busLine* new_line)
/*This function gets the pointer to the new bus line and add it to the end of the list*/
{
	busLine* ptr = head;

	/*if the list is empty, make it head*/
	if (head == nullptr)        
    {   
		new_line->next = head;
		return new_line;
    }

    // go to the last node
    while (ptr->next != nullptr)
    {    
		ptr = ptr->next;
    } 

    //now insert new node after where ptr points to
	new_line->next = ptr->next;
	ptr->next = new_line;
	return head;
}

busLine* add_bus_line_to_beggining_of_list(busLine* new_line)
/*This function gets the pointer to the new bus line and add it to the beginning of the list*/
{ 
	new_line->next = head;
	return new_line;
}

busStop* add_bus_stop_to_end_of_list(busStop* head, busStop* new_stop)
/*This function gets the pointer to the list of the bus stops and add new stop to the end of the list*/
{
	busStop* ptr = head;

	/*if list is empty make it head*/
	if (head == nullptr)        
    {   
		new_stop->right = head;
		new_stop->left = nullptr;
		return new_stop;
    }

    // go to the last node
    while (ptr->right != nullptr)
    {    
		ptr = ptr->right;
    } 

    //now insert new node after where ptr points to
	new_stop->right = ptr->right;
	ptr->right = new_stop;
	new_stop->left = ptr;
	return head;
}

busStop* add_bus_stop_to_beginning_of_list(busStop* head, busStop* new_stop)
/*This function gets the pointer to the list of the bus stops and add new stop to the beginning of the list*/
{
	new_stop->right = head;
	new_stop->left = nullptr;
	head->left = new_stop;
	return new_stop;
}

busStop* add_bus_stop_after_the_given_stop(busStop* head, busStop* new_stop, string previous_bus_stop)
/*This function gets the pointer to the list of the bus stops, pointer to the new stop and name of the previous bus stop
 add new stop after the given stop*/
{
	/*initialize the previous and next stops of the new bus*/
	busStop* adress_previous = find_bus_stop(head, previous_bus_stop);
	busStop* adress_next = adress_previous->right;
	
	/*add it to the after*/
	adress_previous->right = new_stop;
	new_stop->right = adress_next;
	new_stop->left = adress_previous;

	/*if it adds to the end, do not connect the left side of the next bus*/
	if(adress_next != nullptr)
	{
		adress_next->left = new_stop;
	}
	return head;
}

busLine* find_bus_line(string line_to_find)
/*If this function finds the bus line, returns the address of it
If not, returns nullptr. */
{
	busLine * ptr = head;

	/*if list is empty, the bus line cannot be in the list
	so this should return nullptr*/
	if (head == nullptr)
	{
		return nullptr;
	}

	/*if the list is not empty, go over all of the nodes*/
	while (ptr != nullptr)
	{
		/*if it finds the bus line, return the address of the node*/
		if( ptr->busLineName == line_to_find)
		{
			return ptr;
		}

		/*go to next node*/
		ptr = ptr->next;
	}

	/*if the list is not empty and bus line is not in the list, return nullptr*/
	return nullptr;
}

busStop* find_bus_stop(busStop* head, string stop_to_find)
/*If this function finds the bus stop, returns the address of it
If not, returns nullptr. */
{
	busStop * ptr = head;

	/*if list is empty, the bus stop cannot be in the list
	so this should return nullptr*/
	if (head == nullptr)
	{
		return nullptr;
	}

	/*if the list is not empty, go over all of the nodes*/
	while (ptr != nullptr)
	{
		/*if it finds the bus line, return the address of the node*/
		if( ptr->busStopName == stop_to_find)
		{
			return ptr;
		}

		/*go to next node*/
		ptr = ptr->right;
	}

	/*if the list is not empty and bus stop is not in the list, return nullptr*/
	return nullptr;
}

void delete_lineandstops_of_bus_line(busLine* address_of_line)
/*This function deletes the given bus line and stops without dealing with the main list
in order to free the dynamically allocated memory*/
{
	busStop* temp;				
	while (address_of_line->busStops != nullptr) 
	{				
		temp = address_of_line->busStops->right;			
		delete address_of_line->busStops;
		address_of_line->busStops = temp;
	}
	delete address_of_line;
}

busLine* delete_line(busLine* address_of_line)
/*This function deletes the given bus line (which is connected with main list) and stops
in order to free the dynamically allocated memory*/
{
	busLine* temp = head;

	/*if the given line is the first line make the second line head
	and delete the bus line*/
	if(head == address_of_line)
	{
		head = address_of_line->next;
		delete_lineandstops_of_bus_line(address_of_line);
		return head;
	}

	/*go to the line just before the given line*/
	while(temp->next != address_of_line)
	{
		temp = temp->next;
	}

	/*connect the previous and subsequent lines*/
	temp->next = address_of_line->next;

	/*delete the line*/
	delete_lineandstops_of_bus_line(address_of_line);
	return head;
}

busStop* delete_stop(busStop* head_stops, string name_of_stop)
/*This function gets the address of the stops list and name of the stop to be deleted
deletes the stop*/
{
	/*initialize the stop*/
	busStop* stop_to_delete = find_bus_stop(head_stops, name_of_stop);

	/*if stop to be deleted is first stop*/
	if(head_stops == stop_to_delete)
	{
		head_stops = stop_to_delete->right;
		delete stop_to_delete;
		return head_stops;
	}

	/*initialize the previous and subsequent bus stops*/
	busStop* previous = stop_to_delete->left;
	busStop* next = stop_to_delete->right;

	/*connect previous and next stop*/
	previous->right=next;

	/*check whether it is at the end of the list*/
	if(next != nullptr)
	{
		next->left = previous;
	}
	delete stop_to_delete;
	return head_stops;
}

bool are_two_stops_in_the_line(busLine* bus_line, string stop_1, string stop_2)
/*This function gets the address of the bus line and two stops
return true if both of them exist in that line
return false otherwise*/
{
	if((find_bus_stop(bus_line->busStops, stop_1) != nullptr) && (find_bus_stop(bus_line->busStops, stop_2) != nullptr))
	{
		return true;
	}
	return false;
}

void delete_colon(string & busLine_name)
/*This function creates the substring of the given string to get rid of the last character
from index 0 to index (size-2)*/
{
	string result = "";
	for(int i = 0; i< busLine_name.size()-1; i++)
	{
		result += busLine_name[i];
	}

	busLine_name=result;
}

void addBusLine()
/*For menu 2*/
{
	/*get the name of the bus line from the user*/
	string bus_line_name;
	cout << "Enter the name of the new bus line (0 for exit to main menu).\n";
	cin >> bus_line_name;

	/*if bus line name is zero go back to main menu*/
	while(bus_line_name != "0")
	{
		/*if given bus line already exists*/
		while(find_bus_line(bus_line_name)!=nullptr)
		{
			cout << "Bus line already exists: enter a new one (0 for exit)\n";
			cin >> bus_line_name;
		}


		if(bus_line_name != "0")
		{
			/*to check whether list of stops empty*/
			int bus_stop_counter = 0;

			string bus_stop_name = "";

			/*initialize the new list of bus stops*/
			busStop* new_list_of_stops = nullptr;

			/*get the bus stops repeatedly until user enters 0*/
			while(bus_stop_name !="0")
			{
				cout << "Enter the name of the next bus stop (enter 0 to complete)\n";
				cin >> bus_stop_name;
				if(bus_stop_name !="0")
				{
					/*if the stop is given by user already*/
					if(find_bus_stop(new_list_of_stops, bus_stop_name) != nullptr)
					{
						cout << "Bus stop already exists in the line\n";
					}

					/*otherwise add the bus stop to the new list*/
					else
					{
						new_list_of_stops = add_bus_stop_to_end_of_list(new_list_of_stops, new busStop(bus_stop_name, nullptr, nullptr));
						bus_stop_counter++;
					}
				}
			}

			/*check whether the user enters at least 1 valid bus stop*/
			if(bus_stop_counter == 0)
			{
				cout << "You are not allowed to add an empty bus line\n";

				/*go to the main menu*/
				bus_line_name = "0";
			}


			else
			{
				/*display the information of the line given by the user*/
				busLine* new_bus_line = new busLine(bus_line_name, nullptr, new_list_of_stops);
				cout <<"The bus line information is shown below\n";
				printBusLines(new_bus_line);

				/*get the confirmation from the user*/
				string choice;
				cout<<"\nAre you sure? Enter (y/Y) for yes (n/N) for no?\n";
				cin >> choice;

				/*if user confirms the addition
				add new line to the list and display 
				the new version of the list*/
				if(choice == "y" || choice == "Y")
				{
					head = add_bus_line_to_beggining_of_list(new_bus_line);
					cout << endl;
					printBusLines(head);

					/*go to the main menu*/
					bus_line_name = "0";
				}

				/*otherwise free the dynamically alocated memory*/
				else if(choice == "n" || choice == "N")
				{
					delete_lineandstops_of_bus_line(new_bus_line);
					
					/*go to the main menu*/
					bus_line_name = "0";
				}
			}
		}
	}

}

void addBusStop()
/*For menu 3*/
{
	/*get hte bus line name from the user*/
	string bus_line_name;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)\n";
	cin>> bus_line_name;
	
	/*check whether the line exists*/
	if (find_bus_line(bus_line_name) == nullptr && bus_line_name != "0")
	{
		cout << "Bus line cannot be found. Going back to previous menu.\n";
		bus_line_name = "0";
	}

	/*if exists*/
	else if (bus_line_name != "0")
	{
		/*initialzie the pointer to the bus line */
		busLine* bus_line = find_bus_line(bus_line_name);

		/*display the line information*/
		cout << "The bus line information is shown below\n";
		print_one_bus_line(bus_line_name);
			
		/*get the bus stop to be added from the user*/
		string name_of_new_bus_stop;
		cout << "\nEnter the name of the new bus stop\n";
		cin >> name_of_new_bus_stop;

		/*if stop exists already*/
		if(find_bus_stop(bus_line->busStops, name_of_new_bus_stop) != nullptr)
		{
			cout << "Bus stop already exists. Going back to previous menu.\n";
		}

		/*if stop does not exist*/
		else
		{
			/*get the name of the previous bus stop */
			string previous_bus_stop;
			cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)\n";
			cin >> previous_bus_stop;

			/*if user enters 0, add it to the beginning of the line*/
			if(previous_bus_stop =="0")
			{
				find_bus_line(bus_line_name)->busStops = add_bus_stop_to_beginning_of_list(find_bus_line(bus_line_name)->busStops, new busStop(name_of_new_bus_stop, nullptr, nullptr));
				printBusLines(head);
			}

			else
			{
				while(previous_bus_stop != "0")
				{
					/*if stop does not exists ask again*/
					if(find_bus_stop(find_bus_line(bus_line_name)->busStops, previous_bus_stop) == nullptr)
					{
						cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)\n";
						cin >> previous_bus_stop;
					}

					/*if stop exists*/
					if(previous_bus_stop != "0" && find_bus_stop(find_bus_line(bus_line_name)->busStops, previous_bus_stop) != nullptr)
					{
						/*add the stop after the given stop*/
						busStop* previos_stop = find_bus_stop(bus_line->busStops, previous_bus_stop);
						bus_line->busStops = add_bus_stop_after_the_given_stop(bus_line->busStops, new busStop(name_of_new_bus_stop, nullptr, nullptr), previous_bus_stop);
						cout<<endl;
						/*dispaly new version of the list*/
						printBusLines(head);

						/*go back to menu*/
						previous_bus_stop = "0";
					}
				}
			}
		}

	}
}

void deleteBusLine()
/*For menu 4*/
{
	/*get the name of the bus line to be deleted*/
	string bus_line_name;
	cout << "Enter the name of the bus line to delete\n";
	cin >> bus_line_name;

	/*if line does not exist, do not make any change*/
	if(find_bus_line(bus_line_name) == nullptr)
	{
		cout << "Bus line cannot be found. Going back to the previous (main) menu.\n";
	}

	/*othervise delete the line and display the new version of the list*/
	else
	{
		head = delete_line(find_bus_line(bus_line_name));
		printBusLines(head);
	}
}

void deleteBusStop()
{
	/*get the name of the bus line from the user */
	string bus_line;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)\n";
	cin >> bus_line;

	while(bus_line!="0")
	{
		/*if bus linedoes not exist*/
		if(find_bus_line(bus_line) == nullptr)
		{
			cout << "Bus line cannot be found. Going back to previous (main) menu.\n";
			/*go back to main menu*/
			bus_line="0";
		}
		else
		{
			/*display the stops of the line*/
			cout << "The bus line information is shown below\n";
			print_one_bus_line(bus_line);

			/*get the name of the bus stop to be deleted*/
			string bus_stop;
			cout << "\nEnter the name of the bus stop to delete (0 for main menu)\n";
			cin >> bus_stop;

			while(bus_stop !="0")
			{
				/*if the given stop does not exist in the bus line ask again*/
				if(find_bus_stop(find_bus_line(bus_line)->busStops, bus_stop) == nullptr)
				{
					cout<<"Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)\n";
					cin>>bus_stop;
				}

				/*otherwise delete the stop*/
				else
				{
					find_bus_line(bus_line)->busStops = delete_stop(find_bus_line(bus_line)->busStops, bus_stop);

					/*after deletion if the line do not have any stop, delete the line as well*/
					if(find_bus_line(bus_line)->busStops == nullptr)
					{
						delete_line(find_bus_line(bus_line));
					}

					/*display the new version of the list*/
					printBusLines(head);
					bus_stop = "0";
				}
			}

			/*go back to the menu*/
			if(bus_stop == "0")
			{
				bus_line="0";
			}
		}
	}
}

void pathfinder()
{
	busLine* busLine_ptr_first= head;
	bool is_find_start = false;
	bool is_find_finish = false;
	/*get the start point*/
	string start, finish;
	cout<<"Where are you now?\n";
	cin >> start;
	
	/*check whether it is in the table*/
	while(busLine_ptr_first != nullptr)
	{
		/*if the bus stop does not exist in the table*/
		if(find_bus_stop(busLine_ptr_first->busStops, start))
		{
			is_find_start = true;
		}
		busLine_ptr_first = busLine_ptr_first->next;
	}

	if(!is_find_start)
	{
		cout<<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
	}
	else
	{
		cout<<"Where do you want to go?\n";
		cin >> finish;

		/*check whether it is in the table*/
		busLine_ptr_first = head;
		while(busLine_ptr_first != nullptr)
		{
			/*if the bus stop does not exist in the table*/
			if(find_bus_stop(busLine_ptr_first->busStops, finish))
			{
				is_find_finish = true;
			}
			busLine_ptr_first = busLine_ptr_first->next;
		}

		if(!is_find_finish)
		{
			cout<<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		}

		else if(start == finish)
		{
			cout<<"Starting point and destination cannot be same. Going back to previous menu."<<endl;
		}

		else if(is_find_start || is_find_finish)
		{
			bool does_path_found = false;
			bool does_direct_path_found = false;
			busLine_ptr_first = head;

			//for directly one busLine

			/*go through the lines and check whether two stops exist in one line*/
			while(busLine_ptr_first != nullptr)
			{
				if (are_two_stops_in_the_line(busLine_ptr_first, start, finish))
				{
					cout<<"You can go there by ";
					print_between_two_stops(busLine_ptr_first, start, finish);
					cout<<endl;
					does_direct_path_found = true;
				}
				busLine_ptr_first = busLine_ptr_first->next;
			}

			/*if there is no direct route*/
			busLine_ptr_first = head;
			while(!does_direct_path_found && busLine_ptr_first != nullptr)
			{
				//find the lines that have the starting bus stop
				if(find_bus_stop(busLine_ptr_first->busStops, start) != nullptr)
				{
					busStop* busStop_ptr = busLine_ptr_first->busStops;

					/*for every bus stop other than the starting bus stop, find in which lines this stop exists*/
					while(busStop_ptr != nullptr)
					{
						if(busStop_ptr->busStopName != start)
						{
							busLine* busLine_ptr_second= head;
							while(busLine_ptr_second != nullptr)
							{
								if (are_two_stops_in_the_line(busLine_ptr_second, busStop_ptr->busStopName, finish))
								{
									cout<<"You can go there by\t";
									print_between_two_stops(busLine_ptr_first, start, busStop_ptr->busStopName);
									cout<<endl<<"\t\t\t";
									print_between_two_stops(busLine_ptr_second, busStop_ptr->busStopName, finish);
									cout<<endl;
									does_path_found = true;
								}
								busLine_ptr_second = busLine_ptr_second->next;
							}
						}
						busStop_ptr = busStop_ptr->right;
					}
				}
				busLine_ptr_first = busLine_ptr_first->next;
			}

			/*if direct and one interchange paths cannot be found*/
			if(!does_path_found && !does_direct_path_found)
			{
				cout << "Sorry no path from "<<start<<" to "<<finish<<" could be found.\n";
			}
		}
	}
}

void processMainMenu() 
{
	char input;
	do
	{
		if(!consistencyCheck()) 
		{
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) 
		{
			case '0':
				cout << "Thanks for using our program" << endl;
				return;
			case '1':
				printBusLines(head);
				break;
			case '2':
				addBusLine();
				break;
			case '3':
				addBusStop();
				break;
			case '4':
				deleteBusLine();
				break;
			case '5':
				deleteBusStop();
				break;
			case '6':
				pathfinder();
				break;
			default:
				cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu
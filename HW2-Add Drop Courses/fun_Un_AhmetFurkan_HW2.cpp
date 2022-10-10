/****************
*Ahmet Furkan Un*
****************/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct courseNode
{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;

	/*contructor of the struct*/
	courseNode(string course_code, string course_name, vector<int> students_attending_IDs, courseNode * next_node)
	{
		courseCode = course_code;
		courseName = course_name;
		studentsAttendingIDs = students_attending_IDs;
		next = next_node;
	}
};

void print_vector(vector<int> & student_ids)
/*prints all elements of the given vector in order*/
{
	for(int i=0; i < student_ids.size(); i++)
	{
		cout << student_ids[i]<< " ";
	}
}

void print_list(courseNode * head)
/*displays all courses and the ids of the students that are attending this course*/
{
	courseNode *  ptr = head; /*loop variable*/
	while(ptr != NULL )
	{
		/*display course code and course name*/
		cout <<ptr->courseCode <<" " <<ptr->courseName<<": ";

		/*display attending students ids*/
		print_vector(ptr->studentsAttendingIDs);

		/*go to the next node*/
		ptr = ptr->next;
		cout << endl;
	}
}

void print_list_for_menu4(courseNode * head)
/*another version of print_list function
it also checks whether attending students are less than 3 or not*/
{
	courseNode *  ptr = head; /*loop variable*/
	while(ptr != NULL )
	{
		/*display course code and sourse name*/
		cout <<ptr->courseCode <<" " <<ptr->courseName;

		/*if the number of attending students are greater or equal to 3*/
		if(ptr->studentsAttendingIDs.size() >=3)
		{
			cout<<": ";

			/*display ids of the attending students*/
			print_vector(ptr->studentsAttendingIDs);
			cout << endl;
		}

		/*if the number of attending students are smaller than 3*/
		else
		{
			cout<<" ";
			print_vector(ptr->studentsAttendingIDs);
			cout << "-> This course will be closed"<<endl;
		}

		/*go to the next node*/
		ptr = ptr->next;
	}
}

courseNode * find_node(courseNode * head, string course_code)
/*if course exists, returns the addres of the node.
if course does not exist, returns NULL*/
{
	courseNode * ptr = head;

	/*if list is empty, the course cannot be in the list
	so this should return NULL*/
	if (head == NULL)
	{
		return NULL;
	}

	/*if the list is not empty, go over all of the nodes*/
	while (ptr != NULL)
	{
		/*if it finds the course, return the address of the node*/
		if( ptr->courseCode == course_code)
		{
			return ptr;
		}

		/*go to next node*/
		ptr = ptr->next;
	}

	/*if the list is not empty and course is not in the list, return NULL*/
	return NULL;
}

int find_student_id(vector<int> & student_ids, int id)
/*if id exists, returns the index of the id.
if id does not exist, returns -1*/
{
	/*go over all the elements of the vector, if you find the id, retrun the index*/
	for(int i=0; i < student_ids.size(); i++)
	{
		if (student_ids[i] == id)
		{
			return i;
		}
	}

	/*if the id is not found, return -1*/
	return -1;
}

courseNode * AddInOrder(courseNode * head, courseNode * new_node)
/*Taken from CS204 class slides and modified.
pre: list is sorted
post: add new node to list, keep list sorted, return head of new list*/
{
   courseNode *  ptr = head;   // loop variable

   // if new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
    if (head == NULL || new_node->courseName < head->courseName)        
    {   
		new_node->next = head;
		return new_node;
    }

    // check node one ahead so we don't pass!
    while (ptr->next != NULL && ptr->next->courseName < new_node->courseName)
    {    
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node ptr points

    //now insert new node with newkey after where ptr points to
	new_node->next = ptr->next;
	ptr->next = new_node;
	return head;
}

courseNode * Add_notInOrder(courseNode * head, courseNode * new_node)
//pre: list is not sorted
//post: add to the end of the list, list is still not sorted
	
//another version of AddInOrder
//different from the AddInOrder, this list is not sorted
{
   courseNode *  ptr = head;   // loop variable

   // if the list is empty and new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
    if (head == NULL)        
    {   
		new_node->next = head;
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
	return head;
}

void AddInOrder_vector(vector<int> & student_ids, int new_int)
// pre: vector is sorted
// post: add new element to vector, keep vector sorted.
{
	//add new element to the end
	student_ids.push_back(new_int);

	//starting from the end, if the new item is smaller than the previous element
	//switch new element and the previous element. So the list remains sorted
	for(int i=student_ids.size()-1; i >= 0; i--)
	{
		if (new_int < student_ids[i])
		{
			//switch new element with previous element
			int temp = student_ids[i];
			student_ids[i] = new_int;
			student_ids[i+1] = temp;
		}
	}
}

void RemoveInOrder_vector(vector<int> & student_ids, int Remove_int)
// pre: vector is sorted
// post: remove an element from a vector, keep vector sorted.
{
	//find the index using find_student_id function
	int index_of_int = find_student_id(student_ids, Remove_int);

	//starting from the index of the relevant id, 
	//switch the relevant id with the next one until it is the last element
	for(int i=index_of_int; i < student_ids.size()-1; i++)
	{
		int temp = student_ids[i+1];
		student_ids[i+1] = Remove_int;
		student_ids[i] = temp;
	}

	//pop the last element
	student_ids.pop_back();
}

courseNode * convert_stringline_to_new_linked_list(const string &input_line)
//given a line of string which includes courses and ids
//convert this information into a new linked list
{
	//create an empty linked lsit
	courseNode * head = NULL;
	string course_code, course_name;
	int student_id;
	istringstream input_line_stream(input_line);
	bool is_end = false; //to check whether we are at the end or not
	while(!is_end)
	{
		input_line_stream >> course_code >> course_name;
		vector<int> student_ids;
		
		//after getting course name and course code, 
		//repeatedly get student id until the next word is not an integer
		while(input_line_stream >> student_id)
		{
			//put this ids in a vector
			student_ids.push_back(student_id);
		}

		//if the size of the vector is 0, we are at the end
		if(student_ids.size() == 0)
		{
			is_end = true;
		}

		//if we are not at the end
		else
		{
			//add new node the the list
			head = Add_notInOrder(head, new courseNode(course_code, course_name, student_ids, NULL));

			//clear the stream so that we can continue with the another course and ids
			input_line_stream.clear();
		}
	}

	//return the head of linked list
	return head;
}

void delete_linked_list(courseNode * head)
//delete the linked list to free the allocated memory
{
	courseNode *temp;				
	while (head != NULL) 
	{				
		temp = head->next;			
		delete head;
		head = temp;
	}
}

int main()
{
	//create an empty linked list to store all of the data
	courseNode * head = NULL;
	string filename;
	ifstream input;
	cout << "Please enter file name: ";
	cin >> filename;
	input.open(filename.c_str());
	if (input.fail())
	{
		cout <<"Error, couldn't open the file!"<< endl;
	}
	else
	{
		cout << "Successfully opened file "<< filename<<endl;
		string input_line;

		//check whether we are at the end or the line is empty
		//if not go over each line
		while (getline(input, input_line)&& input_line.size() >0)
		{
			string course_code, course_name;
			int student_id;
			istringstream input_line_stream(input_line);

			//get relevant informaiton from the line
			input_line_stream >> course_code >> course_name >> student_id;

			//if the course at this line is not in the node, create it and put the student in it
			if (find_node(head, course_code) == NULL)
			{
				vector<int> student_ids;
				student_ids.push_back(student_id);
				head = AddInOrder(head, new courseNode(course_code, course_name, student_ids, NULL));
			}

			//if the course is in the list, go to the vector of that course and add the id to this vector
			else
			{
				//check whether the student is already in or not
				//if id is not in the vector, add it
				if(find_student_id(find_node(head, course_code)->studentsAttendingIDs, student_id) == -1)
				{
					AddInOrder_vector(find_node(head, course_code)->studentsAttendingIDs, student_id);
				}
			}
		}
		cout<<"The linked list is created."<<endl;
		cout<<"The initial list is:"<<endl;
		print_list(head);

		//this variable tells whether the user enters the choice 4
		bool is_over = false;

		while(!is_over)
		{
			cout << endl;
			int choice;

			//show the menu and get the choice
			cout<<"Please select one of the choices: " <<endl;
			cout<<"1. Add to List" <<endl;
			cout<<"2. Drop from List" <<endl;
			cout<<"3. Display List" <<endl;
			cout<<"4. Finish Add/Drop and Exit" <<endl;
			cin >> choice;

			if(choice == 1)
			{
				cout<<"Give the student ID and the course names and course codes that he/she wants to add:"<<endl;
				string input_line;
				cin.clear();
				cin.sync();
				getline(cin, input_line);

				//convert this line to a linked list using funciton
				courseNode* list_to_add = convert_stringline_to_new_linked_list(input_line);

				//go over with all the nodes of list_to_add
				while(list_to_add != NULL)
				{
					//if the relevant course in the list_to_add is not in the actual list,
					//add the course to the actual list
					if (find_node(head, list_to_add->courseCode) == NULL)
					{
						vector<int> student_ids;
						head = AddInOrder(head, new courseNode(list_to_add->courseCode, list_to_add->courseName , student_ids, NULL));
						cout<< list_to_add->courseCode <<" does not exist in the list of Courses. It is added up."<<endl;
					}	

					//for every id in the relevant course,
					for( int i=0; i < list_to_add->studentsAttendingIDs.size(); i++)
					{
						//if the id is not in the vector of the course in actual list, add the student
						if(find_student_id(find_node(head, list_to_add->courseCode)->studentsAttendingIDs, list_to_add->studentsAttendingIDs[i]) == -1)
						{
							AddInOrder_vector(find_node(head, list_to_add->courseCode)->studentsAttendingIDs, list_to_add->studentsAttendingIDs[i]);
							cout << "Student with id "<<list_to_add->studentsAttendingIDs[i]<<" is enrolled to "<<list_to_add->courseCode<<"."<<endl;
						}

						//if the id is in the vector of the course in actual list, tell that you cannot add
						else
						{
							cout << "Student with id "<<list_to_add->studentsAttendingIDs[i]<<" already is enrolled to "<<list_to_add->courseCode<<". No action taken."<<endl;
						}
					}
					
					//go to the next course
					list_to_add = list_to_add ->next;
				}

				//free the allocated memory from list_to_add
				delete_linked_list(list_to_add);
			}

			else if(choice == 2)
			{
				cout<<"Give the student ID and the course names and course codes that he/she wants to drop:"<<endl;
				string input_line;
				cin.clear();
				cin.sync();
				getline(cin, input_line);

				//convert this line to a linked list using funciton
				courseNode* list_to_drop = convert_stringline_to_new_linked_list(input_line);
				
				//go over with all the nodes of list_to_drop
				while(list_to_drop != NULL)
				{
					//if the course is not in the actual list, for every id in the vector, tell that you cannot drop 
					if (find_node(head, list_to_drop->courseCode) == NULL)
					{
						for( int i=0; i < list_to_drop->studentsAttendingIDs.size(); i++)
						{
							cout<<"The "<<list_to_drop->courseCode<<" course is not in the list, thus student with id "<<list_to_drop->studentsAttendingIDs[i]<<" can\'t be dropped."<<endl;
						}
					}

					//if the course is in the actual list
					else
					{
						for( int i=0; i < list_to_drop->studentsAttendingIDs.size(); i++)
						{
							//and also if the student is not in the vector of the course in the actual list
							//tell that you cannot drop
							if(find_student_id(find_node(head, list_to_drop->courseCode)->studentsAttendingIDs, list_to_drop->studentsAttendingIDs[i]) == -1)
							{
								cout << "Student with id "<<list_to_drop->studentsAttendingIDs[i]<<" is not enrolled to "<<list_to_drop->courseCode<<", thus he can\'t drop that course."<<endl;
							}

							//if the student is taking that course
							else
							{
								//remove s/he from the vector
								RemoveInOrder_vector(find_node(head, list_to_drop->courseCode)->studentsAttendingIDs, list_to_drop->studentsAttendingIDs[i]);
								cout << "Student with id "<<list_to_drop->studentsAttendingIDs[i]<<" has dropped "<<list_to_drop->courseCode<<"."<<endl;
							}
						}
					}

					//go to the next course
					list_to_drop = list_to_drop ->next;
				}

				//free the allocated memory from list_to_drop
				delete_linked_list(list_to_drop);
			}

			else if(choice == 3)
			{
				cout <<"The current list of course and the students attending them:"<<endl;
				print_list(head);
			}

			else if(choice == 4)
			{
				cout <<"The add/drop period is finished. Printing the final list of courses and students attending them."<<endl;
				cout <<"NOTE: Courses with less than 3 students will be closed this semester."<<endl;
				print_list_for_menu4(head);

				//add drop is over, it wont enter the while loop again
				is_over = true;

				//free the allocated memory from actual list
				delete_linked_list(head);
			}
		}
	}
	return 0;
}
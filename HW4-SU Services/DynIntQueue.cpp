/****************************************************
* Taken from Lecture Materials of Week 5 of CS204   *
* Modified by Ahmet Furkan Un                       *
****************************************************/

#include <iostream>
#include "DynIntQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynIntQueue::DynIntQueue()
{
	front = NULL;
	rear = NULL;   
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynIntQueue::enqueue(DynQueueNode newNode)
{       
	DynQueueNode * node = new DynQueueNode(newNode.function_name, newNode.name, newNode.id);
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = node;
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = node;
		rear = rear->next;
	} 
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynIntQueue::dequeue(DynQueueNode &node)
{
	DynQueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		node.function_name = front->function_name;
		node.id = front->id;
		node.name = front->name;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynIntQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynIntQueue::clear()
{
	DynQueueNode temp;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(temp); //delete all elements
}

//************************************************
// Destructor to free the dynamically allocated  *
// memory.                                       *
//************************************************
DynIntQueue::~DynIntQueue()
{
	clear();
}
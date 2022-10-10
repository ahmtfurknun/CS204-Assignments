/****************************************************
* Taken from Lecture Materials of Week 5 of CS204   *
* Modified by Ahmet Furkan Un                       *
****************************************************/

#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H
using namespace std;

struct DynQueueNode
{
	string function_name;
	string name;
	int id;
	DynQueueNode *next;

	//default constructor
	DynQueueNode()
	{
		function_name = "";
		name = "";
		id = -1;
		next = NULL;
	}

	//constructor
	DynQueueNode(string function, string Name, int Id, DynQueueNode *ptr = NULL)
	{
		function_name = function;
		name = Name;
		id = Id;
		next = ptr;
	}
};

class DynIntQueue
{
private:
	// These track the front and rear of the queue.
	DynQueueNode *front;
	DynQueueNode *rear;	
public:
	// Constructor.
	DynIntQueue();
	
	//Destructor.
	~DynIntQueue();

	// Member functions.
	void enqueue(DynQueueNode);
	void dequeue(DynQueueNode&);
	bool isEmpty() const;     
	void clear();
};
#endif
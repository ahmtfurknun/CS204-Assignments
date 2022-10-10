/****************************************************
* Taken from Lecture Materials of Week 5 of CS204   *
* Modified by Ahmet Furkan Un                       *
****************************************************/

#ifndef INTQUEUE_H
#define INTQUEUE_H
#include <vector>
using namespace std;

struct QueueNode
{
	string function_name;
	string name;
	int id;
	QueueNode *next;
	QueueNode()
	{
		function_name = "";
		name = "";
		id = -1;
		next = NULL;
	}

	QueueNode(string function, string Name, int Id, QueueNode *ptr = NULL)
	{
		function_name = function;
		name = Name;
		id = Id;
		next = ptr;
	}

};

class IntQueue
{
private:
	vector <QueueNode> queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	IntQueue(int);  //constructor, parameter is capacity
  	void enqueue(QueueNode); 
  	void dequeue(QueueNode&);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif
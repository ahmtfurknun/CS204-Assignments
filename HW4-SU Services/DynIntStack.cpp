/****************************************************
* Taken from Lecture Materials of Week 5 of CS204   *
* Modified by Ahmet Furkan Un                       *
****************************************************/

#include <iostream>
#include "dynintstack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(StackNode newNode)
{
	StackNode* node = new StackNode(newNode.command, newNode.value, newNode.function_name);
	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = node;
		node->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		node->next = top;
		top = node;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(StackNode &node)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		node.command = top->command;
		node.function_name = top->function_name;
		node.value = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

//************************************************
// Destructor to free the dynamically allocated  *
// memory.                                       *
//************************************************
DynIntStack::~DynIntStack()
{
	StackNode temp;
	while(!isEmpty())
	{
		pop(temp);
	}
	delete top;
}

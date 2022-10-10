/****************************************************
* Taken from Lecture Materials of Week 5 of CS204   *
* Modified by Ahmet Furkan Un                       *
****************************************************/

using namespace std;
struct StackNode
{
	string command;
	string value;
	string function_name;
	StackNode *next;
	
	//default constructor
	StackNode()
	{
		command = "";
		value = "";
		function_name = "";
		next = NULL;
	}

	//constructor
	StackNode(string Command, string Value, string Function_name)
	{
		command = Command;
		value = Value;
		function_name = Function_name;
		next = NULL;
	}
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);//constructor
	~DynIntStack();//destructor

	//member functions
	void push(StackNode);
	void pop(StackNode&);
	bool isEmpty(void);
};

//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 9: Exceptions and Templates                                          |
//---------------------------------------------------------------------------------+
#include "TUStack.h"
using namespace std;

int main() {
	// Test a unique stack of int values
	TUStack<int> intStack(5);

	// Try popping an empty stack
	try {
		int i = intStack.pop();
	}
	catch (TUStackException<int> e) {
		e.PrintMessage(cout);
	}

	// Try inserting duplicate items
	try {
		intStack.push(3);
		
		intStack.push(4);
		cout << "Item Popped: " << intStack.pop() << endl;

		intStack.push(3);
	}
	catch (TUStackException<int> e) {
		e.PrintMessage(cout);
	}

	// Test a unique stack of string objects
	TUStack<string> strStack(3);

	// Try inserting too many items
	try {
		strStack.push("Hello World");
		strStack.push("Templates can be fun, yet lead to frustrating linker errors");
		strStack.push("It is better to validate input than to catch excpetions");

		strStack.push("Why not check if the stack is full before pushing?");
	}
	catch (TUStackException<string> e) {
		e.PrintMessage(cout);
	}

	// Try accessing an item out of bounds
	try {
		cout << "Item Popped: " << strStack.pop() << endl << endl;
		cout << "Element at index 0: " << strStack[0] << endl << endl;
		cout << "Attempting to access index 2..." << endl;
		strStack[2];
	}
	catch (TUStackException<string> e) {
		e.PrintMessage(cout);
	}

	system("pause");
	return 0;
}
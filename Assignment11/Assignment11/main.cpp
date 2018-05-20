//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 11: Dynamic Stack Application                                        |
//---------------------------------------------------------------------------------+
#include "SQData.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int opOrder(char op) {
	switch (op) {
	case '*': case '/':
		return 4;
	case '+': case '-':
		return 3;
	case '(': case ')':
		return 2;
	case '[': case ']':
		return 1;
	default:
		return 0;
	}
}

string toPostFix(string preFix) {
	stringstream postFix;
	Stack<char> stack;
	stack.push('[');

	for (unsigned int i = 0; i < preFix.length(); ++i) {
		// If not an operator: simply append it to the string
		if (opOrder(preFix[i]) == 0) {
			postFix << preFix[i];
		}

		// If an opening parenthesis: push onto the stack
		else if (preFix[i] == '(') {
			stack.push(preFix[i]);
		}

		// If a closing parenthesis: pop off operators until you find the corresponding opening parenthesis
		else if (preFix[i] == ')') {
			char popped = stack.pop();
			while (popped != '(') {
				postFix << popped;
				popped = stack.pop();
			}
		}

		// Else: pop off all higher order operators and push onto the stack
		else {
			int order = opOrder(preFix[i]);
			while (opOrder(stack.peek()) >= order && stack.peek() != '[') {
				postFix << stack.pop();
			}

			if (preFix[i] != ']') {
				stack.push(preFix[i]);
			}
		}
	}
	
	// Pop off all remaining operators
	while (opOrder(stack.peek()) > opOrder(']')) {
		postFix << stack.pop();
	}

	// Return the results
	return postFix.str();
}

int main() {
	cout << "Postfix Converter!" << endl
		<< "-------------------------------" << endl << endl
		<< "a+b+c       -->     " << toPostFix("a+b+c]") << endl
		<< "Should be ...       ab+c+" << endl
		<< endl
		<< "a+(b+c)       -->   " << toPostFix("a+(b+c)]") << endl
		<< "Should be ...       abc++" << endl
		<< endl
		<< "(a+b)+c       -->   " << toPostFix("(a+b)+c") << endl
		<< "Should be ...       ab+c+" << endl
		<< endl
		<< "a-b*c         -->   " << toPostFix("a-b*c") << endl
		<< "Should be ...       abc*-" << endl
		<< endl
		<< "(a/b)*(c/d)   -->   " << toPostFix("(a/b)*(c/d)") << endl
		<< "Should be ...       ab/cd/*" << endl
		<< endl
		<< "a/(b+c*d-e)   -->   " << toPostFix("a/(b+c*d-e)") << endl
		<< "Should be ...       abcd*+e-/" << endl
		<< endl
		<< "a-b*c+d/e     -->   " << toPostFix("a-b*c+d/e") << endl
		<< "Should be ...       abc*-de/+" << endl
		<< endl;

	system("pause");
	return 0;
}
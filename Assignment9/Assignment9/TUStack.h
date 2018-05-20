#ifndef TUSTACK_H
#define TUSTACK_H

// External Dependencies
#include <iostream>
#include <string>

template <typename T>
class TUStackException {
public:
	std::string Message;
	int Size, Position;
	bool T_Instance;
	T Element;

	TUStackException(std::string m, int s, int p) {
		T_Instance = false;

		Message = m;
		Size = s;
		Position = p;
	}
	TUStackException(std::string m, int s, int p, T e) {
		T_Instance = true;
		Element = e;

		Message = m;
		Size = s;
		Position = p;
	}
	void PrintMessage(std::ostream& out) {
		out << endl
			<< "--------------------------------------------" << endl << endl
			<< "Exception Caught!" << endl
			<< Message << endl
			<< "Stack Size: " << Size << endl
			<< "Stack Head: " << Position << endl;
		if (T_Instance) {
			out << "Element Insertion Attempted: " << Element << endl;
		}
		out << endl
			<< "--------------------------------------------" << endl << endl;
	}
};

// Generic Stack class implemented with dynamically-allocated array
template <typename T>
class TUStack {
private:
	int n, top;
	T* stack;

public:
	// Constructor and Destructor
	TUStack(int);
	TUStack(const TUStack<T>&);
	~TUStack();

	// Overloaded operator=
	TUStack<T>& operator=(const TUStack<T>&);
	T operator[](int) const;

	// Standard methods
	void push(T);
	T pop();

	// Helper methods
	int size() const { return n; }
	int Position() const { return top; }
	bool isEmpty() const { return top == 0; }
	bool isFull() const { return top == n; }
};

//---------------------------------------------------------------------------------+
// Constructors and Destructor, operator=                                          |
// Manage the inital values and clean up any used memory when finished             |
//---------------------------------------------------------------------------------+
template <typename T>
TUStack<T>::TUStack(int nSize) {
	top = 0;
	n = nSize;
	stack = new T[n];
}

template <typename T>
TUStack<T>::TUStack(const TUStack<T>& rhs) {
	top = rhs.top;
	n = rhs.n;
	stack = new T[n];
	for (int i = 0; i < n; ++i) {
		stack[i] = rhs.stack[i];
	}
}

template <typename T>
TUStack<T>::~TUStack() {
	delete[] stack;
	stack = NULL;
}

template <typename T>
TUStack<T>& TUStack<T>::operator=(const TUStack<T>& rhs) {
	// Empty the stack
	delete[] stack;

	// Copy the right hand stack
	top = rhs.top;
	n = rhs.n;
	stack = new T[n];
	for (int i = 0; i < n; ++i) {
		stack[i] = rhs.stack[i];
	}

	return *this;
}

//---------------------------------------------------------------------------------+
// Overloaded [] access operator                                                   |
// I see no point to this since, by design, stacks only *ever* care what's on top  |
//---------------------------------------------------------------------------------+
template <typename T>
T TUStack<T>::operator[](int i) const {
	if (i > top - 1) {
		throw TUStackException<T>("Out of Bounds Exception", n, top);
	}

	return stack[i];
}

//---------------------------------------------------------------------------------+
// void push                                                                       |
// Inserts a <T> at the head (top) of the stack                                    |
//---------------------------------------------------------------------------------+
template <typename T>
void TUStack<T>::push(T c) {
	if (isFull()) {
		throw TUStackException<T>("Stack Overflow Exception", n, top, c);
		std::cout << "Why does it continue after doing this?" << endl;
	}

	// I see no point to this but as the assignment requires...
	// Check each element to make sure no duplicate values are inserted
	for (int i = 0; i < top; ++i) {
		if (stack[i] == c) {
			throw TUStackException<T>("Stack Duplication Exception", n, top, c);
		}
	}

	stack[top++] = c;
}

//---------------------------------------------------------------------------------+
// <T> pop                                                                         |
// Gets Node at head, removes it from the stack, and returns the value it held     |
//---------------------------------------------------------------------------------+
template <typename T>
T TUStack<T>::pop() {
	if (isEmpty()) {
		throw TUStackException<T>("Stack Underflow Exception", n, top);
	}

	return stack[(top-- - 1)];
}

#endif
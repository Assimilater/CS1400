#ifndef SQDATA_H
#define SQDATA_H

// External Dependencies
#include <iostream>

namespace sqdata {
	// Doubly Linked-List Node class upon which Stack and Queue build
	template <typename T>
	struct Node {
		T val;
		Node<T>
			*next,
			*prev;

		Node(T v) {
			val = v;
			next = NULL;
			prev = NULL;
		}
	};
}

// Generic Stack class implemented with Linked-List
template <typename T>
class Stack {
private:
	int cnt;
	sqdata::Node<T>
		*head,
		*tail;
public:
	// Constructor and Destructor
	Stack() {
		head = NULL;
		tail = NULL;
		cnt = 0;
	}
	Stack(const Stack<T>& rhs) {
		sqdata::Node<T>* current = rhs.tail;
		while (current != NULL) {
			push(current->val);
			current = current->prev;
		}
	}
	~Stack() {
		while (cnt > 0) {
			pop();
		}
	}

	// Overloaded = operator
	Stack<T>& operator=(const Stack<T>& rhs) {
		// Empty the stack
		while (cnt > 0) {
			pop();
		}

		// Copy the right hand stack
		sqdata::Node<T>* current = rhs.tail;
		while (current != NULL) {
			push(current->val);
			current = current->prev;
		}

		return *this;
	}

	// Standard methods
	void push(T c) {
		sqdata::Node<T>* n = new sqdata::Node<T>(c);
		n->next = head;

		if (head == NULL) {
			tail = n;
		}
		else {
			head->prev = n;
		}
		head = n;

		cnt++;
	}
	T pop() {
		if (head == tail) {
			tail = NULL;
		}

		T val = head->val;

		sqdata::Node<T>* ptr = head->next;
		delete head;
		head = ptr;

		if (head != NULL) {
			head->prev = NULL;
		}
		cnt--;

		return val;
	}
	T peek() { return head->val; }

	// Helper methods
	int size() const { return cnt; };
	bool isEmpty() const { return cnt == 0; };
};

#endif
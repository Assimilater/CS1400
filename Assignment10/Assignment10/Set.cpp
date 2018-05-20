#include "Set.h"
using namespace std;

// Access methods
int Set::operator[](const int index) const {
	Node *node = head;
	for (int i = 0; i < index && node != NULL; ++i) {
		node = node->next;
	}

	if (node == NULL) {
		throw OutofBoundsException(index);
	}
	else {
		return node->value;
	}
}

bool Set::Find(const int val) const {
	Node *node = head;
	while (node != NULL && node->value != val) { node = node->next; }

	if (node == NULL) {
		cout << "Integer '" << val << "' not found in set";
		return true;
	}

	cout << "Integer '" << val << "' found in set";
	return false;
}

// Basic Linked List Methods
void Set::Print(ostream& out) const {
	Node *node = head;
	out << "{ ";
	while (node != NULL) {
		out << node->value << (node->next != NULL ? ", " : " ");
		node = node->next;
	}
	out << "}";
}

void Set::Insert(int val) {
	Node
		*insert = new Node(val),
		*right = head,
		*left = NULL;
	
	while (right != NULL && val > right->value) {
		left = right;
		right = right->next;
	}

	if (right != NULL && right->value == val) {
		throw DuplicateException(val);
		return;
	}
	else if (left != NULL) {
		left->next = insert;
	}
	else {
		head = insert;
	}

	insert->next = right;
	++cnt;
}

void Set::Delete(int val) {
	Node
		*find = head,
		*left = head;

	while (find != NULL && val != find->value) {
		left = find;
		find = find->next;
	}

	if (find != NULL) {
		left->next = find->next;
		delete find;
		--cnt;
	}
}

// Overloaded Set Unary Operators
bool Set::operator<(const Set& rho) const {
	Node
		*right = rho.head,
		*left = this->head;

	while (left != NULL) {
		while (right != NULL && left->value > right->value) {
			right = right->next;
		}

		if (right == NULL || left->value != right->value) { return false; }
		left = left->next;
	}
	return true;
}

Set Set::operator^(const Set& rho) const {
	Node
		*right = rho.head,
		*left = this->head;

	Set temp;

	while (left != NULL) {
		while (right != NULL && right->value > left->value) {
			right = right->next;
		}

		if (right != NULL && left->value == right->value) {
			temp.Insert(left->value);
		}
		left = left->next;
	}

	return temp;
}

Set Set::operator+(const Set& rho) const {
	Node
		*right = rho.head,
		*left = this->head;

	Set temp;

	while (left != NULL) {
		while (right != NULL && right->value > left->value) {
			temp.Insert(right->value);
			right = right->next;
		}

		if (right != NULL && left->value != right->value) {
			temp.Insert(left->value);
		}
		left = left->next;
	}
	while (right != NULL) {
		temp.Insert(right->value);
		right = right->next;
	}

	return temp;
}

Set Set::operator-(const Set& rho) const {
	Node
		*right = rho.head,
		*left = this->head;

	Set temp;

	while (left != NULL) {
		while (right != NULL && right->value < left->value) {
			//temp.Insert(right->value);
			right = right->next;
		}

		if (right != NULL) {
			if (left->value != right->value) {
				temp.Insert(left->value);
			}
			else {
				right = right->next;
			}
		}

		left = left->next;
	}
	/*
	while (right != NULL) {
		temp.Insert(right->value);
		right = right->next;
	}
	*/

	return temp;
}

ostream& operator<<(ostream& out, const Set& obj) { obj.Print(out); return out; }
istream& operator>>(istream& in, Set& obj) { obj.Insert(in); return in; }

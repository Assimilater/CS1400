#ifndef CS1410_SET_H
#define CS1410_SET_H

#include <string>
#include <iostream>

class Set {
private:
	class Node {
	private:
		void clear() { if (next != NULL) { delete next; } }
		void copy(const Node& rho) {
			value = rho.value;
			next = rho.next != NULL ? new Node(*rho.next) : NULL;
		}

	public:
		int value;
		Node *next;

		~Node() { clear(); }
		Node(int val) { value = val; next = NULL; }
		Node(const Node& rho) { copy(rho); }
		Node& operator=(const Node& rho) { clear(); copy(rho); return *this; }
	};

public:
	class DuplicateException {
	public:
		int value;
		DuplicateException(int v) { value = v; }
	};

	class OutofBoundsException {
	public:
		int i;
		OutofBoundsException(int index) { i = index; }
	};

private:
	int cnt;
	Node *head;
	void clear() { if (head != NULL) { delete head; } }
	void copy(const Set& rho) {
		cnt = rho.cnt;
		head = rho.head != NULL ? new Node(*rho.head) : NULL;
	}
	
public:
	~Set() { clear(); }
	Set() { cnt = 0; head = NULL; }
	Set(const Set& rho) { copy(rho); }
	Set& operator=(const Set& rho) { clear(); copy(rho); return *this; }

	int Size() const { return cnt; }
	int operator[](const int) const;
	bool Find(const int) const;
	
	void Print(std::ostream&) const;
	void Print() const { Print(std::cout); }

	void Insert(int);
	void Insert(std::istream& in) { int val; in >> val; Insert(val); }

	void Delete(int);

	bool operator<(const Set&) const;
	Set operator^(const Set&) const;
	Set operator+(const Set&) const;
	Set operator-(const Set&) const;
};

// iostream operators pertaining to class Set
std::ostream& operator<<(std::ostream&, const Set&);
std::istream& operator>>(std::istream&, Set&);

#endif

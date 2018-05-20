#ifndef CS_2410_BST_H
#define CS_2410_BST_H

// External Dependencies
#include <iostream>

template <typename T>
class BST {
private:
	T value;
	int size, height;
	BST *Left, *Right;

	void clear() {
		if (Left != NULL) { delete Left; }
		if (Right != NULL) { delete Right; }
	}
	void copy(const BST& rho) {
		value = rho.value;
		size = rho.size;
		height = rho.height;
		Left = rho.Left != NULL ? new BST(*rho.Left) : NULL;
		Right = rho.Right != NULL ? new BST(*rho.Right) : NULL;
	}

public:
	BST(T val) {
		value = val;
		size = 1;
		height = 0;
		Left = NULL;
		Right = NULL;
	}
	~BST() { clear(); }
	BST(const BST& rho) { copy(rho); }
	BST& operator=(const BST& rho) { clear(); copy(rho); return *this; }

	void Insert(T val) {
		if (value >= val) {
			if (Left != NULL) {
				Left->Insert(val);
			}
			else {
				Left = new BST(val);
			}

			// If insertion makes the left subtree taller, make the current subtree taller as well
			if (Left->height == height) {
				++height;
			}
		}
		if (value < val) {
			if (Right != NULL) {
				Right->Insert(val);
			}
			else {
				Right = new BST(val);
			}
			
			// If insertion makes the right subtree taller, make the current subtree taller as well
			if (Right->height == height) {
				++height;
			}
		}

		// Update the size after insertion
		++size;
	}
	bool Find(T val) {
		if (value == val) { return true; }
		if (value > val && Left != NULL) { return Left->Find(val); }
		if (value < val && Right != NULL) { return Right->Find(val); }
		return false;
	}
	int Size() { return size; }
	int Height() { return height; }

	void Print(std::ostream& out) {
		// Print to 'out' using post-order traversal
		if (Left != NULL) { Left->Print(out); }
		if (Right != NULL) { Right->Print(out); }
		out << "Memory Location: " << this << "   Value: " << value << endl;
	}
};

#endif

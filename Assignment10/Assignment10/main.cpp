//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 10: Linked Lists                                                     |
//---------------------------------------------------------------------------------+
#include "Set.h"
#include <iostream>
using namespace std;

int main() {
	Set S1, S2, S3;

	S1.Insert(1);
	S1.Insert(4);
	S1.Insert(9);
	S1.Insert(16);

	S3.Insert(4);
	S3.Insert(9);

	S2.Insert(1);
	S2.Insert(2);
	S2.Insert(3);
	S2.Insert(5);
	S2.Insert(8);
	S2.Insert(13);
	S2.Insert(21);

	try {
		S2.Insert(1);
	}
	catch (Set::DuplicateException e) {
		cout << "Attempted to insert duplicate element: '" << e.value << "'" << endl;
	}

	if (S1.Find(16) == true) {
		cout << "16 is found in S1" << S1 << endl;
		cout << "Find() function is correct." << endl; // this is correct
	}
	else {
		cout << "16 is not found in S1" << S1 << endl;
		cout << "WARNING: Find() function is not correct." << endl;
	}

	cout
		<< "S1: Size: " << S1.Size() << " Elements: " << S1 << endl
		<< "S2: Size: " << S2.Size() << " Elements: " << S2 << endl
		<< "S3: Size: " << S3.Size() << " Elements: " << S3 << endl
		<< "S1 < S2: " << (S1 < S2 ? "true" : "false") << endl
		<< "S3 < S1: " << (S3 < S1 ? "true" : "false") << endl
		<< "S1 ^ S2: " << (S1 ^ S2) << endl
		<< "S1 + S2: " << (S1 + S2) << endl
		<< "S1 - S2: " << (S1 - S2) << endl
		<< "S3[0]: " << S3[0] << endl << endl
		<< "Insert a value into S3: ";

	try {
		cin >> S3;
		cout << "Insertion Successful." << endl;
	}
	catch (Set::DuplicateException e) {
		cout << "Attempted to insert duplicate element: '" << e.value << "'" << endl;
	}
	cout << "Updated S3: " << S3 << endl;

	system("pause");
	return 0;
}

//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 12: Binary Trees and Recursion                                       |
//---------------------------------------------------------------------------------+
#include "BST.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

ostream& operator<<(ostream& out, BST<string> dict) { dict.Print(out); return out; }

int main() {
	const int NUM_PUNCTUATION = 8;
	const char PUNCTUATION[NUM_PUNCTUATION] = {'"', ',', ':', '.', '!', '?', '(', ')'};
	BST<string> *dict;
	vector<string> words;
	string temp, temp_lower;

	cout << "Parsing dictionary. This may take a moment..." << endl;

	ifstream fin("dictionary.txt");
	if (fin) {
		// Read the file
		getline(fin, temp);
		while (!fin.eof() && temp != "") {
			words.push_back(temp);
			getline(fin, temp);
		}
		fin.close();

		// Randomize the list so as to avoid a BST with height n and populate the BST
		random_shuffle(words.begin(), words.end());

		cout
			<< "Finished parsing dictionary..." << endl << endl
			<< "Testing copy constructor and operator= of BST..." << endl;

		// Verify public methods of BST
		BST<string> BST1(words[0]);
		for (int i = 1; i < 10; ++i) {
			BST1.Insert(words[i]);
		}
		BST<string> BST2(BST1);
		
		cout
			<< "Expect similar values but different memory addresses..." << endl << endl
			<< "BST 1" << endl << BST1 << endl << endl
			<< "BST 2" << endl << BST2 << endl << endl;

		BST2 = BST1;

		cout << "BST 3" << endl << BST2 << endl << endl;

		cout
			<< "Finished testing copy constructor and operator= of BST..." << endl
			<< "Other public methods assumed correct if program executes properly..." << endl
			<< "Populating dictionary. This may take a moment..." << endl;

		// Continue with normal operations
		dict = new BST<string>(words[0]);
		for (unsigned int i = 1; i < words.size(); ++i) {
			dict->Insert(words[i]);
		}

		cout
			<< "Finished populating dictionary..." << endl << endl
			<< "Dictionary's BST Data:" << endl
			<< "Nodes: " << dict->Size() << endl
			<< "Height: " << dict->Height() << endl
			<< endl
			<< "Parsing letter..." << endl;

		fin.open("letter.txt");
		if (fin) {
			cout << endl;

			fin >> temp;
			while (!fin.eof() && temp != "") {
				// Remove punctuation
				for (int i = 0; i < NUM_PUNCTUATION; ++i) {
					char p = PUNCTUATION[i];
					while (temp.find(p) != string::npos) {
						temp.replace(temp.find(p), 1, "");
					}
				}

				// Conver to lowercase
				temp_lower = temp;
				for (unsigned int i = 0; i < temp_lower.length(); ++i) {
					temp_lower[i] = tolower(temp_lower[i]);
				}

				if (!dict->Find(temp_lower)) {
					cout << "Spelling error: " << temp << endl;
				}

				fin >> temp;
			}
		}
		else {
			cout << "Unable to open letter..." << endl;
		}

		delete dict;
		dict = NULL;
	}
	else {
		cout << "Unable to open dictionary..." << endl;
	}

	system("pause");
	return 0;
}
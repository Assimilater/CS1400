//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 4: Inheritance and Object Composition                                |
//---------------------------------------------------------------------------------+
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Person.h"
#include "Package.h"
#include "OvernightPackage.h"
#include "TwoDayPackage.h"

using namespace std;

// Prototypes
bool run();
void printLabel(const Package&, const double);
char GetChar(char Prompt[]);
istream& operator>>(istream&, Person&);

int main() {
	bool exec = true;
	while (exec) {
		exec = run();
	}
	
	system("pause");
	return 0;
}

bool run() {
	string file;
	cout << "Enter a valid file-path (ie C:\\Users\\User\\Desktop\\package.txt)" << endl
		<< "\t(You can click and drag onto the console): ";

	getline(cin, file);
	
	// Remove quotes if found
	if (file[0] == '"') {
		file = file.substr(1, string::npos);
	}
	if (file[file.size() - 1] == '"') {
		file = file.substr(0, file.length() - 1);
	}

	// Check file
	ifstream fin(file);
	if (!fin) {
		cout << "File not found..." << endl << endl;
		return true;
	}

	while (!fin.eof()) {
		// Read file contents
		char type;
		fin >> type;

		// Check for appropriate values
		if (type != 'P' && type != 'p' && type != 'O' && type != 'o' && type != 'T' && type != 't') {
			cout << "Cannot read file..." << endl << endl;
			fin.close();
			return true;
		}

		// Read remaining data
		int weight; double cost; Person sender, receiver;

		fin >> weight;
		fin >> cost;
		fin.ignore();

		fin >> sender;
		fin >> receiver;

		// Read last line if appropriate and print out the correct label
		if (type == 'O' || type == 'o') {
			double diff;
			fin >> diff;

			OvernightPackage package(sender, receiver, weight, cost, diff);
			printLabel(package, package.Cost());
		}
		else if (type == 'T' || type == 't') {
			double diff;
			fin >> diff;

			TwoDayPackage package(sender, receiver, weight, cost, diff);
			printLabel(package, package.Cost());
		}
		else {
			Package package(sender, receiver, weight, cost);
			printLabel(package, package.Cost());
		}
	}
	fin.close();

	// Prompt the user if they wish to print another label
	char goAgain = GetChar("Print another label? (Y or N): ");
	while (goAgain != 'Y' && goAgain != 'y' && goAgain != 'N' && goAgain != 'n') {
		cout << "Unrecognized input..." << endl << endl;
		goAgain = GetChar("Print another label? (Y or N): ");
	}
	
	return goAgain == 'Y' || goAgain == 'y';
}

//---------------------------------------------------------------------------------+
// void printLabel                                                                 |
// Given a package object print the shipping label                                 |
//---------------------------------------------------------------------------------+
void printLabel(const Package& obj, const double cost) {
	system("cls");

	cout << fixed << setprecision(2)
		<< "Shipping Label:" << endl
		<< "Package Weight: " << obj.GetWeight() << endl
		<< "Cost to Ship: $" << cost << endl
		<< endl
		<< "From: " << obj.GetSender().GetName() << endl
		<< obj.GetSender().GetAddress() << endl
		<< obj.GetSender().GetCity() << ", " << obj.GetSender().GetState() << " " << obj.GetSender().GetZip() << endl
		<< endl
		<< "To: " << obj.GetReceiver().GetName() << endl
		<< obj.GetReceiver().GetAddress() << endl
		<< obj.GetReceiver().GetCity() << ", " << obj.GetReceiver().GetState() << " " << obj.GetReceiver().GetZip() << endl
		<< endl;
	
	system("pause");
	system("cls");
}

//---------------------------------------------------------------------------------+
// char GetChar                                                                    |
// Implemented to reduce redundant code, gets a single character from the user     |
//---------------------------------------------------------------------------------+
char GetChar(char Prompt[]) {
	char input;

	cout << Prompt;

	cin >> input;
	cin.ignore();

	return input;
}

//---------------------------------------------------------------------------------+
// Overload the extraction operator for class Person for simplicity's sake         |
//---------------------------------------------------------------------------------+
istream& operator>>(istream& in, Person& obj) {
	std::string temp;

	// Name
	getline(in, temp);
	obj.SetName(temp);

	// Address
	getline(in, temp);
	obj.SetAddress(temp);

	// City
	getline(in, temp);
	obj.SetCity(temp);

	// State
	getline(in, temp);
	obj.SetState(temp);

	// Zip
	getline(in, temp);
	obj.SetZip(temp);

	return in;
}
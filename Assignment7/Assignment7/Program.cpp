//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 7: Binary File Operations                                            |
//---------------------------------------------------------------------------------+
#include "Friend.h"
using namespace std;

//---------------------------------------------------------------------------------+
// void openFile                                                                   |
// Promps the user to overwrite the data file if it exits, otherwise create it     |
//---------------------------------------------------------------------------------+
void openFile(fstream& file){
	char choice;
	file.open("myNetwork.dat", ios::in | ios::binary);

	if (file) {
		// Close the file
		file.close();

		// Ask the user if they want to overwrite the file
		do {
			cout << "\"myNetwork.dat\" already exists. Overwrite file? (Y/N): ";
			cin >> choice;
			cin.ignore();
			if (toupper(choice) == 'Y') {
				// Open a new file and exit
				file.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::trunc);
				return;
			}
			else if (toupper(choice) == 'N') {
				// Open the existing file and exit
				file.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);
				return;
			}
			else {
				cout << "Please enter 'Y' for yes, or 'N' for no" << endl;
			}
		} while (true);
	}
	
	// If the program reaches this point, the file does not exist so open a new one.
	file.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::trunc);
}

//---------------------------------------------------------------------------------+
// char GetChoice                                                                  |
// Display the main menu and return the 1-character response from the user         |
//---------------------------------------------------------------------------------+
char GetChoice() {
	char choice;
	cout
		<< "*** Network of My Friends ***" << endl
		<< "A: Add a Friend" << endl
		<< "R: Remove a Friend by ID Number" << endl
		<< "M: Modify a Friend's Information by ID Number" << endl
		<< "S: Search Interests" << endl
		<< "D: Display \"myNetwork.dat\" Database Information" << endl
		<< "L: List the Oldest and the Youngest Friends' Information" << endl
		<< "E: Exit" << endl
		<< endl
		<< "Selection: ";
	cin >> choice;

	// At this point there is still a \r\n stored in the input buffer, so ignore for reliability
	cin.ignore();
	return choice;
}

int main() {
	fstream file;
	openFile(file);
	system("cls");

	char choice;
	while (true) {
		choice = GetChoice();
		switch (choice) {
		case 'A': case 'a':
			// Add a Friend
			AddFriend(file);
			break;
		case 'R': case 'r':
			// Remove a Friend by ID Number
			RemoveFriend(file);
			break;
		case 'M': case 'm':
			// Modify a Friend's Information by ID Number
			ModifyFriend(file);
			break;
		case 'S': case 's':
			// Search Interests
			SearchInterest(file);
			break;
		case 'D': case 'd':
			// Display "myNetwork.dat" Database Information
			DisplayFriends(file);
			break;
		case 'L': case 'l':
			// List the Oldest and the Youngest Friends' Information
			ListFriends(file);
			break;
		case 'E': case 'e':
			// Close the file and exit
			file.close();
			exit(0);
		default:
			// Invalid input
			cout << "Unrecognized command. Please try again." << endl;
		}
		cout << endl;
		system("pause");
		system("cls");
	}
	return -1;
}
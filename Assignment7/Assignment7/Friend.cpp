#include "Friend.h"
using namespace std;

//---------------------------------------------------------------------------------+
// void AddFriend                                                                  |
// Add a friend to the end of the binary file                                      |
//---------------------------------------------------------------------------------+
void AddFriend(fstream& file) {
	Friend temp;
	cout << "*** Add a new friend profile" << endl;

	// Get the screen name
	cout << "Screen Name: ";
	cin.getline(temp.screen_name, SCREENNAME_SIZE);

	// Get the interests
	cout << "Interests: ";
	cin.getline(temp.interests, INTERESTS_SIZE);

	// Get the age
	cout << "Age: ";
	cin >> temp.age;
	cin.ignore();

	// Add to the end of the file
	file.seekp(0, ios::end);
	file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
}

//---------------------------------------------------------------------------------+
// void RemoveFriend                                                               |
// Prompt the user for an ID to remove, show them the info, confirm, and remove    |
//---------------------------------------------------------------------------------+
void RemoveFriend(fstream& file) {
	int ID, numFriends = CountFriends(file);
	Friend temp;
	cout << "*** Remove a friend ***" << endl;

	// Get the ID
	cout << "Enter the ID of a friend to remove: ";
	cin >> ID;
	cin.ignore();

	if (ID < 0 || numFriends < ID) {
		cout << ID << " is not a valid ID." << endl;
		if (numFriends != 0) {
			cout << "Highest is " << numFriends << endl;
		}
		else {
			cout << "There are no friends in your database!" << endl;
		}
	}
	else {
		file.seekg((sizeof(Friend)) * (ID - 1), ios::beg);
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));

		// Output the information
		PrintFriend(temp, ID);

		// Get a confirmation of deletion or request to cancel from the user
		char c;
		do {
			cout << "Do you really want to delete this friend from your database? (Y/N): ";
			cin >> c;
			cin.ignore();
			if (toupper(c) == 'Y') {
				// Exit the loop if they decide to proceed with the deletion
				break;
			}
			else if (toupper(c) == 'N') {
				// Exit the function if they decide to cancel
				return;
			}
			else {
				// Re-prompt if given invalid input
				cout << "Please enter 'Y' for yes, or 'N' for no" << endl;
			}
		} while (true);

		// Proceed with the deletion
		for (int i = ID; i < numFriends; ++i) {
			// Read the next friend in the database
			file.seekg((sizeof(Friend)) * (i), ios::beg);
			file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));

			// Rewrite the current friend in the database with the data from the next friend
			file.seekp((sizeof(Friend)) * (i - 1), ios::beg);
			file.write(reinterpret_cast<char*>(&temp), sizeof(Friend));
		}

		// Put an empty value in the last slot in the file
		Empty(temp);
		file.seekp((sizeof(Friend)) * (numFriends - 1), ios::beg);
		file.write(reinterpret_cast<char*>(&temp), sizeof(Friend));
	}
}

//---------------------------------------------------------------------------------+
// void SearchInterest                                                             |
// Prompt the user for a keyphrase to search for                                   |
// List all screennames that contain that keyphrase                                |
//---------------------------------------------------------------------------------+
void SearchInterest(fstream& file) {
	Friend temp;

	// Get the keyphrase from the user
	string keyphrase;
	cout << "Search Keyword: ";
	getline(cin, keyphrase);

	if(keyphrase == "") {
		cout << "Cannot search for an empty search parameter." << endl;
		return;
	}

	int numFriends = CountFriends(file);
	bool found = false;

	// Loop through each friend and check their interests against the keyphrase
	file.seekg(0, ios::beg);
	for (int i = 0; i < numFriends; ++i) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));
		if(!IsEmpty(temp)) {
			if(tolower(string(temp.interests)).find(tolower(keyphrase), 0) != string::npos) {
				cout << "*** Friend " << i + 1 << ": " << temp.screen_name << endl;
				found = true;
			}
		}
	}

	if(!found) {
		cout << "No matching interests found." << endl;
	}
}

//---------------------------------------------------------------------------------+
// void ModifyFriend                                                               |
// Prompt the user for an ID, information to replace, and confirm updating friend  |
//---------------------------------------------------------------------------------+
void ModifyFriend(fstream& file) {
	int ID;
	Friend _old, _new;
	int numFriends = CountFriends(file);

	cout << "*** Modify a friend ***" << endl;

	// Get the ID
	cout << "Enter the ID of a friend to modify: ";
	cin >> ID;
	cin.ignore();

	if (ID < 0 || numFriends < ID) {
		cout << ID << " is not a valid ID." << endl;
		if (numFriends != 0) {
			cout << "Highest is " << numFriends << endl;
		}
		else {
			cout << "There are no friends in your database!" << endl;
		}
	}
	else {
		// Get the screen name
		cout << "Screen Name: ";
		cin.getline(_new.screen_name, SCREENNAME_SIZE);

		// Get the interests
		cout << "Interests: ";
		cin.getline(_new.interests, INTERESTS_SIZE);

		// Get the age
		cout << "Age: ";
		cin >> _new.age;
		cin.ignore();

		file.seekg((sizeof(Friend)) * (ID - 1), ios::beg);
		file.read(reinterpret_cast<char*>(&_old), sizeof(Friend));

		// Output the information
		cout << endl << "Are you sure you want to clear this data:" << endl;
		PrintFriend(_old, ID);

		cout << "And replace it to this data?" << endl;
		PrintFriend(_new, ID);

		// Get a confirmation of deletion or request to cancel from the user
		char c;
		do {
			cout << "(Y/N): ";
			cin >> c;
			cin.ignore();
			if (toupper(c) == 'Y') {
				// Exit the loop if they decide to proceed with the update
				break;
			}
			else if (toupper(c) == 'N') {
				// Exit the function if they decide to cancel
				return;
			}
			else {
				// Re-prompt if given invalid input
				cout << "Please enter 'Y' for yes, or 'N' for no" << endl;
			}
		} while (true);

		// Overwrite the information
		file.seekp((sizeof(Friend)) * (ID - 1), ios::beg);
		file.write(reinterpret_cast<char*>(&_new), sizeof(Friend));
	}
}

//---------------------------------------------------------------------------------+
// void DisplayFriends                                                             |
// Display all information in the list with indicies                               |
//---------------------------------------------------------------------------------+
void DisplayFriends(fstream& file) {
	Friend temp;

	// Count the number of friends in the file
	int numFriends = CountFriends(file);

	if (numFriends == 0) {
		cout << "No friends to display" << endl;
		return;
	}

	// Iteratively read and output each friend
	file.seekg(0, ios::beg);
	for (int i = 0; i < numFriends; ++i) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));
		PrintFriend(temp, i + 1);
	}
}

//---------------------------------------------------------------------------------+
// void ListFriends                                                                |
// Display all non-empty screennames in alphabetical order                         |
//---------------------------------------------------------------------------------+
void ListFriends(fstream& file) {
	Friend temp;
	int min = -1, max = -1;
	int numFriends = CountFriends(file);
	
	// Loop through each friend and find the min and max ages
	file.seekg(0, ios::beg);
	for (int i = 0; i < numFriends; ++i) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));
		if(!IsEmpty(temp)) {
			if (max == -1) {
				max = temp.age;
				min = temp.age;
			}
			else if (temp.age > max) {
				max = temp.age;
			}
			else if (temp.age < min) {
				min = temp.age;
			}
		}
	}

	if(max == -1) {
		cout << endl << "No friends to display" << endl;
		return;
	}

	cout << endl << "-------------------------------------------------------" << endl;

	// Loop through again and print out the oldest friends
	cout << "Oldest Friends:" << endl << endl;
	file.seekg(0, ios::beg);
	for (int i = 0; i < numFriends; ++i) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));
		if (temp.age == max) {
			PrintFriend(temp, i + 1);
		}
	}

	cout << endl << "-------------------------------------------------------" << endl;

	// Loop through again and print out the youngest friends
	cout << "Youngest Friends:" << endl << endl;
	file.seekg(0, ios::beg);
	for (int i = 0; i < numFriends; ++i) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(Friend));
		if (temp.age == min) {
			PrintFriend(temp, i + 1);
		}
	}
}

//---------------------------------------------------------------------------------+
// int CountFriends                                                                |
// Using simple arithmatic, count how many friends are in the file                 |
//---------------------------------------------------------------------------------+
int CountFriends(fstream& file) {
	file.seekg(0, ios::end);
	return (int)file.tellp() / sizeof(Friend);
}

//---------------------------------------------------------------------------------+
// void PrintFriend                                                                |
// Print the information for a single friend object                                |
//---------------------------------------------------------------------------------+
void PrintFriend(Friend& f, int ID) {
	cout
		<< "ID: " << ID << endl
		<< "Screen Name: " << f.screen_name << endl
		<< "Interests: " << f.interests << endl
		<< "Age: " << f.age << endl
		<< endl;
}

//---------------------------------------------------------------------------------+
// bool IsEmpty                                                                    |
// Return true if the given object is empty, otherwise false                       |
//---------------------------------------------------------------------------------+
bool IsEmpty(Friend& f) {
	return
		f.age == 0 &&
		strcmp(f.interests, EMPTY_STRING) == 0 &&
		strcmp(f.screen_name, EMPTY_STRING) == 0;
}

//---------------------------------------------------------------------------------+
// void Empty                                                                      |
// Empty the given object of data                                                  |
//---------------------------------------------------------------------------------+
void Empty(Friend& f) {
	f.age = 0;
	strcpy_s(f.screen_name, strlen(EMPTY_STRING) + 1, EMPTY_STRING);
	strcpy_s(f.interests, strlen(EMPTY_STRING) + 1, EMPTY_STRING);
}

//---------------------------------------------------------------------------------+
// string tolower                                                                  |
// An extension of the standard tolower() method to apply it to string             |
//---------------------------------------------------------------------------------+
string tolower(string convert) {
	for (int j = 0; j < (int)convert.size(); j++) {
		convert[j] = tolower(convert[j]);
	}
	return convert;
}
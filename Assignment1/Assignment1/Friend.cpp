#include <iostream>
#include "Friend.h"

//---------------------------------------------------------------------------------+
// void AddFriend                                                                  |
// Add a friend to the first empty element in the friends array                    |
//---------------------------------------------------------------------------------+
void AddFriend(Friend friends[], int size) {
	int i = 0;
	bool found = false;
	while(i < size && !found) {
		if(IsEmpty(friends[i])) {
			found = true;
		}
		else {
			i++;
		}
	}
	if(!found) {
		std::cout << "Sorry, the database is full.";
	}
	else {
		std::cout << "*** Add a new friend profile" << std::endl;
		
		// Get the screen name
		std::cout << "Screen Name: ";
		std::getline(std::cin, friends[i].screen_name);

		// Get the interests
		std::cout << "Interests: ";
		std::getline(std::cin, friends[i].interests);

		// Get the age
		std::cout << "Age: ";
		std::cin >> friends[i].age;

		// At this point there is still a \r\n stored in the input buffer, so ignore for reliability
		std::cin.ignore();
	}
}

//---------------------------------------------------------------------------------+
// void RemoveFriend                                                               |
// Display all friends by index and screen name                                    |
// Prompt the user for an index to delete and set that element to "empty"          |
//---------------------------------------------------------------------------------+
void RemoveFriend(Friend friends[], int size) {
	int remove = -1;
	bool found = false;

	std::cout << "*** Remove a friend ***" << std::endl;
	for(int i = 0; i < size; i++) {
		if(!IsEmpty(friends[i])) {
			std::cout << i << ": " << friends[i].screen_name << std::endl;
			found = true;
		}
	}
	if(!found) {
		std::cout << "No friends found" << std::endl;
	}
	else {
		std::cout << std::endl << "Which to remove: ";
		std::cin >> remove;

		// At this point there is still a \r\n stored in the input buffer, so ignore for reliability
		std::cin.ignore();

		if(remove >= 0 && remove < size && !IsEmpty(friends[remove])) {
			Empty(friends[remove]);
		}
		else {
			std::cout << "No friend found at index: " << remove << std::endl;
		}
	}
}

//---------------------------------------------------------------------------------+
// void SearchInterest                                                             |
// Prompt the user for a keyphrase to search for                                   |
// List all screennames that contain that keyphrase                                |
//---------------------------------------------------------------------------------+
void SearchInterest(Friend friends[], int size) {
	std::string keyphrase;
	std::cout << "Search Keyword: ";
	std::getline(std::cin, keyphrase);

	if(keyphrase == "") {
		std::cout << "Cannot search for an empty search parameter." << std::endl;
		return;
	}

	bool found = false;
	for(int i = 0; i < size; i++) {
		if(!IsEmpty(friends[i])) {
			if(tolower(friends[i].interests).find(tolower(keyphrase), 0) != std::string::npos) {
				std::cout << "*** " << friends[i].screen_name << std::endl;
				found = true;
			}
		}
	}

	if(!found) {
		std::cout << "No matching interests found." << std::endl;
	}
}

//---------------------------------------------------------------------------------+
// void DisplayFriends                                                             |
// Display all information in the list with indicies                               |
//---------------------------------------------------------------------------------+
void DisplayFriends(Friend friends[], int size) {
	bool found = false;
	for(int i = 0; i < size; i++) {
		if(!IsEmpty(friends[i])) {
			found = true;
			std::cout
				<< "Index " << i << ":" << std::endl
				<< "Screen Name: " << friends[i].screen_name << std::endl
				<< "Interests: " << friends[i].interests << std::endl
				<< "Age: " << friends[i].age << std::endl
				<< std::endl;
		}
	}
	if(!found) {
		std::cout << "No friends to display" << std::endl;
	}
}

//---------------------------------------------------------------------------------+
// void ListFriends                                                                |
// Display all non-empty screennames in alphabetical order                         |
//---------------------------------------------------------------------------------+
void ListFriends(Friend friends[], int size) {
	bool found = false;
	// Sort a copy so the original array remains unmodified
	Friend copy[NUM_FRIENDS];
	for(int i = 0; i < size; i++) { copy[i] = friends[i]; }

	BubbleSort(copy, size);

	for(int i = 0; i < size; i++) {
		if(!IsEmpty(copy[i])) {
			found = true;
			std::cout << copy[i].screen_name << std::endl;
		}
	}
	if(!found) {
		std::cout << "No friends to display" << std::endl;
	}
}

//---------------------------------------------------------------------------------+
// float ReportAge                                                                 |
// Calculate the average age of all non-empty friends                              |
//---------------------------------------------------------------------------------+
float ReportAge(Friend friends[], int size) {
	int cnt = 0;
	float sum = 0;
	for(int i = 0; i < size; i++) {
		if(friends[i].age != 0) {
			sum += friends[i].age;
			cnt++;
		}
	}
	if(cnt == 0) return 0;
	return sum / cnt;
}

//---------------------------------------------------------------------------------+
// bool IsBefore                                                                   |
// Return true if the two elements are in order                                    |
// Conditions are by screen name alphabetically, then by age                       |
//---------------------------------------------------------------------------------+
bool IsBefore(Friend &friend1, Friend &friend2) {
	// Let's not compare EMPTY_STRING with meaningful data
	if(IsEmpty(friend1) && !IsEmpty(friend2)) { return false; }
	if(IsEmpty(friend1) && IsEmpty(friend2)) { return true; }

	return friend1.screen_name < friend2.screen_name;
}

//---------------------------------------------------------------------------------+
// The following two methods were provided by the instructor                       |
// BubbleSort was slightly modified: indention + when size decrementation occurs   |
//---------------------------------------------------------------------------------+
void BubbleSort(Friend array[], int size) {
	bool done = false;
	while(!done) {
		done = true;
		for(int n = 0; n < size - 1; n++) {
			if(!IsBefore(array[n], array[n + 1])) {
				Swap(array[n], array[n + 1]);
				done = false;
			}
		}
		size--;
	}
}
void Swap(Friend &a, Friend &b) {
	Friend temp;
	temp = a;
	a = b;
	b = temp;
}

//---------------------------------------------------------------------------------+
// bool IsEmpty                                                                    |
// Return true if the given object is empty, otherwise false                       |
//---------------------------------------------------------------------------------+
bool IsEmpty(Friend &a_friend) {
	return
		a_friend.age == 0 &&
		a_friend.interests == EMPTY_STRING &&
		a_friend.screen_name == EMPTY_STRING;
}

//---------------------------------------------------------------------------------+
// void Empty                                                                      |
// Empty the given object of data                                                  |
//---------------------------------------------------------------------------------+
void Empty(Friend &a_friend) {
	a_friend.age = 0;
	a_friend.interests = EMPTY_STRING;
	a_friend.screen_name = EMPTY_STRING;
}

//---------------------------------------------------------------------------------+
// std::string tolower                                                             |
// An extension of the standard tolower() method to apply it to std::string        |
//---------------------------------------------------------------------------------+
std::string tolower(std::string convert) {
	for(int j = 0; j < (int)convert.size(); j++) {
		convert[j] = tolower(convert[j]);
	}
	return convert;
}
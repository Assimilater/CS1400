//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 1: Manage a Social Network Database                                  |
//---------------------------------------------------------------------------------+
#include <iostream>
#include "Friend.h"

// Function Prototypes
char GetChoice();

//---------------------------------------------------------------------------------+
// The following program manages simple information about five 'friends'.          |
// It provides a user with a menu and continues to execute the requested methods   |
// Until the user gives the command to exit the program.                           |
//---------------------------------------------------------------------------------+
int main() {
	Friend friends[NUM_FRIENDS];

	char choice;
	while(true) {
		choice = GetChoice();
		switch(choice) {
		case 'A': case 'a':
			// Add a Friend
			AddFriend(friends, NUM_FRIENDS);
			break;
		case 'R': case 'r':
			// Remove a Friend
			RemoveFriend(friends, NUM_FRIENDS);
			break;
		case 'S': case 's':
			// Search Interests
			SearchInterest(friends, NUM_FRIENDS);
			break;
		case 'D': case 'd':
			// Display All Friends
			DisplayFriends(friends, NUM_FRIENDS);
			break;
		case 'L': case 'l':
			// List All Friends in Alphabetic Order Based on ScreenName
			ListFriends(friends, NUM_FRIENDS);
			break;
		case 'C': case 'c':
			// Calculate the Average Age of All Friends in My Network
			std::cout
				<< "The average age of all friends in my network is "
				<< ReportAge(friends, NUM_FRIENDS) << std::endl;
			break;
		case 'E': case 'e':
			// Exit
			exit(0);
		default:
			// Invalid input
			std::cout << "Unrecognized command. Please try again." << std::endl;
		}
		std::cout << std::endl;
		system("cls");
	}
	return -1;
}

//---------------------------------------------------------------------------------+
// char GetChoice                                                                  |
// Display the main menu and return the 1-character response from the user         |
//---------------------------------------------------------------------------------+
char GetChoice() {
	char choice;
	std::cout
		<< "*** Network of My Friends ***" << std::endl
		<< "A: Add a Friend" << std::endl
		<< "R: Remove a Friend" << std::endl
		<< "S: Search Interests" << std::endl
		<< "D: Display All Friends" << std::endl
		<< "L: List All Friends in Alphabetic Order Based on ScreenName" << std::endl
		<< "C: Calculate the Average Age of All Friends in My Network" << std::endl
		<< "E: Exit" << std::endl
		<< std::endl
		<< "Selection: ";
	std::cin >> choice;

	// At this point there is still a \r\n stored in the input buffer, so ignore for reliability
	std::cin.ignore();
	return choice;
}
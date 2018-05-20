//---------------------------------------------------------------------------------+
// John Call - johnkc1992@gmail.com                                                |
// Assignment 2: Connect N Game                                                    |
//---------------------------------------------------------------------------------+
#include <iostream>
#include <ctime>
#include "Game.h"
using namespace std;

int GetSize();
int main() {
	// Seed the randomizer
	srand(static_cast<unsigned int>(time(NULL)));

	bool playAgain = true;
	int size;
	Game *active;

	while(playAgain) {
		system("cls");
		cout << "Welcome to Connect-N-Game!" << endl;

		// Get user input for game size
		size = GetSize();
		while(size < Game::MIN_SIZE || size > Game::MAX_SIZE) {
			cout << endl
				<< "Sorry, this game does not support a connection that size." << endl
				<< "Please try again." << endl
				<< endl;
			size = GetSize();
		}

		// Play the game
		active = new Game(size);
		playAgain = active->Play();
		delete active;
	}

	cout << endl
		<< "Thanks for Playing!" << endl;
	system("pause");
	return 0;
}

//---------------------------------------------------------------------------------+
// int GetSize                                                                     |
// Ask the user for the size of the game and return the integer value              |
//---------------------------------------------------------------------------------+
int GetSize() {
	int size;
	cout << "How big of a connection is required to win?" << endl
		<< "Enter a number between " << Game::MIN_SIZE << " and " << Game::MAX_SIZE << ": ";

	cin >> size;
	cin.ignore();
	return size;
}
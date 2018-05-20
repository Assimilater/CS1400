#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Game.h"

char GetChar(char Prompt[]);
bool isInt(char val);
int toInt(char val);

//---------------------------------------------------------------------------------+
// Constructor                                                                     |
// Create a new board given the number of consecutive tokens required to win       |
//---------------------------------------------------------------------------------+
Game::Game(int size) {
	WinLength = size;

	Rows = size + EXTRA_ROWS;
	Cols = size + EXTRA_COLS;
	
	// Dynamically Allocate a two-dimensional array to represent the empty board
	Board = new char*[Cols];
	for(int i = 0; i < Cols; i++) {
		Board[i] = new char[Rows];
		for(int j = 0; j < Rows; j++) {
			Board[i][j] = EMPTY;
		}
	}

	GameOver = false;
	PlayersTurn = rand() % 2 == 0;
}

//---------------------------------------------------------------------------------+
// Destructor                                                                      |
// Delete the board and free up memory for use                                     |
//---------------------------------------------------------------------------------+
Game::~Game() {
	for(int i = 0; i < Cols; i++) {
		delete[] Board[i];
		Board[i] = NULL; // Necessary?
	}
	delete[] Board;
	Board = NULL;
}

//---------------------------------------------------------------------------------+
// bool Play                                                                       |
// Get user input until the game is over, return if the user want to play again    |
//---------------------------------------------------------------------------------+
bool Game::Play() {
	char input;
	int move;
	bool valid;

	// Continue to play the game
	while(!GameOver) {
		DrawBoard();
		if(!PlayersTurn) {
			valid = false;
			while(!valid) {
				move = rand() % Cols;
				valid = !ColumnFull(move);
			}
			GameOver = CompleteSet(Animate(COMPUTER, move));
			if(!GameOver) {
				PlayersTurn = true;
			}
		}
		else {
			// Show the options
			std::cout << "1-" << Cols << ": Move in the Corresponding Column" << std::endl
				<< "Q: Quit Game" << std::endl;

			// Get user input and execute on it as soon as it's validated
			input = GetChar("Your Move: ");
			while(!ExecuteInput(input)) {
				input = GetChar("Your Move: ");
			}
		}
	}

	// Announce the winner
	std::cout << "The " << (PlayersTurn ? "Player" : "Computer") << " Wins! Yay!" << std::endl;
	
	// Does the user want to play again?
	std::cout << std::endl;
	input = GetChar("Play Again? (Y or N): ");
	while(tolower(input) != 'y' && tolower(input) != 'n') {
		input = GetChar("Play Again? (Y or N): ");
	}

	return tolower(input) == 'y';
}

//---------------------------------------------------------------------------------+
// char SpotValue                                                                  |
// Simple accessor function to get the value at a given cartesian on the board     |
//---------------------------------------------------------------------------------+
char Game::SpotValue(Cartesian spot) {
	return Board[spot.Col][spot.Row];
}

//---------------------------------------------------------------------------------+
// char SpotValue                                                                  |
// Overload of the above method, sets the given cartesion to the given value first |
//---------------------------------------------------------------------------------+
char Game::SpotValue(Cartesian spot, char value) {
	Board[spot.Col][spot.Row] = value;
	return Board[spot.Col][spot.Row];
}

//---------------------------------------------------------------------------------+
// bool ColumnFull                                                                 |
// Return true if the given column is full                                         |
//---------------------------------------------------------------------------------+
bool Game::ColumnFull(int column) {
	return SpotValue(Cartesian(column, Rows - 1)) != EMPTY;
}

//---------------------------------------------------------------------------------+
// bool CompleteSet                                                                |
// Use recursion to determine if the given element is part of a winning set        |
//---------------------------------------------------------------------------------+
bool Game::CompleteSet(Cartesian spot) {
	int cnt;
	char opponent = SpotValue(spot);

	// Handle extraneous case
	if(opponent == EMPTY) { return false; }

	for(Angle pVector = UP; pVector < DOWN; pVector = (Angle)(pVector + 1)) {
		cnt = 1;
		cnt += CountMatch(Transform(spot, pVector), opponent, pVector);
		if(cnt >= WinLength) { return true; }

		cnt += CountMatch(Transform(spot, Reverse(pVector)), opponent, Reverse(pVector));
		if(cnt >= WinLength) { return true; }
	}
	return false;
}

//---------------------------------------------------------------------------------+
// int CountMatch                                                                  |
// Recursive function that counts all matching objects in a given direction        |
//---------------------------------------------------------------------------------+
int Game::CountMatch(Cartesian spot, char opponent, Angle aDir) {
	if(spot.Col >= Cols || spot.Row >= Rows || spot.Col < 0 || spot.Row < 0) {
		return 0;
	}
	if(SpotValue(spot) != opponent) {
		return 0;
	}
	return 1 + CountMatch(Transform(spot, aDir), opponent, aDir);
}

//---------------------------------------------------------------------------------+
// Cartesian Transform                                                             |
// Returns a transformed cartesion in the given direction                          |
//---------------------------------------------------------------------------------+
Cartesian Game::Transform(Cartesian spot, Angle aDir) {
	switch(aDir) {
	case UP_LEFT:
		spot.Col--;
	case UP:
		spot.Row++;
		break;

	case DOWN_LEFT:
		spot.Row--;
	case LEFT:
		spot.Col--;
		break;

	case DOWN_RIGHT:
		spot.Col++;
	case DOWN:
		spot.Row--;
		break;

	case UP_RIGHT:
		spot.Row++;
	case RIGHT:
		spot.Col++;
		break;
	}
	return spot;
}

//---------------------------------------------------------------------------------+
// Game::Angle Reverse                                                             |
// Returns the angle that is opposite the given angle                              |
//---------------------------------------------------------------------------------+
Game::Angle Game::Reverse(Angle aDir) {
	if((int)aDir >= 4) {
		return (Angle)(aDir - 4);
	}
	return (Angle)(aDir + 4);
}

//---------------------------------------------------------------------------------+
// void DrawBoard                                                                  |
// Draws the current status of the board and who's turn it is                      |
//---------------------------------------------------------------------------------+
void Game::DrawBoard() {
	system("cls");
	PrintCentered((std::string)("Connect ") + std::to_string(WinLength) + "!");
	std::cout << std::endl;
	
	// Print the full table
	DrawIdentifiers();
	std::cout << std::setfill('-') << std::setw(Cols * 4 + 1) << "-" << std::endl;

	for(int j = Rows - 1; j >= 0; j--) {
		// Print the data
		std::cout << "| ";
		for(int i = 0; i < Cols; i++) {
			std::cout << SpotValue(Cartesian(i, j)) << " | ";
		}

		// Print a divider
		std::cout << std::endl
			<< std::setfill('-') << std::setw(Cols * 4 + 1) << "-" << std::endl;
	}

	DrawIdentifiers();

	// Print who's turn it is
	std::cout << std::endl;
	PrintCentered((std::string)(PlayersTurn ? "Player's " : "Computer's ") + "Turn");
	std::cout << std::endl;
}

//---------------------------------------------------------------------------------+
// void DrawIdentifiers()                                                          |
// Output a row with properly spaced column identifiers for the user               |
//---------------------------------------------------------------------------------+
void Game::DrawIdentifiers() {
	for(int j = 1; j <= Cols; j++) {
		std::cout << "  " << j << " ";
	}
	std::cout << std::endl;
}

//---------------------------------------------------------------------------------+
// void PrintCentered                                                              |
// Output a given string centered with the dynamically sized board                 |
//---------------------------------------------------------------------------------+
void Game::PrintCentered(std::string text) {
	std::cout
		<< std::setw((Cols * 4 - (int)text.length()) / 2)
		<< std::setfill(' ')
		<< " "
		<< text.c_str()
		<< std::endl;
}

//---------------------------------------------------------------------------------+
// void Animate                                                                    |
// Make the move of the given player and return the Cartesian for the spot filled  |
//---------------------------------------------------------------------------------+
Cartesian Game::Animate(char opponent, int column) {
	int i = Rows - 1;
	
	SpotValue(Cartesian(column, i), opponent);
	DrawBoard();

	// Move down one until you hit the bottom
	while(i > 0 && SpotValue(Cartesian(column, i - 1)) == EMPTY) {
		Sleep(250);
		SpotValue(Cartesian(column, i), EMPTY);
		SpotValue(Cartesian(column, i - 1), opponent);
		DrawBoard();
		i--;
	}
	
	DrawBoard();
	return Cartesian(column, i);
}

//---------------------------------------------------------------------------------+
// bool ExecuteInput                                                               |
// Perform the user specified task - returns false if input is invalid             |
//---------------------------------------------------------------------------------+
bool Game::ExecuteInput(char input) {
	if(tolower(input) == 'q') {
		GameOver = true;
		PlayersTurn = false;
		return true;
	}

	if(isInt(input)) {
		int move = toInt(input);

		if(move <= 0 || move > Cols) {
			std::cout << std::endl
				<< "Column " << move << " does not exist in this game." << std::endl
				<< std::endl;
			return false;
		}
		
		if(ColumnFull(move - 1)) {
			std::cout << std::endl
				<< "Column " << move << " is full." << std::endl
				<< std::endl;
			return false;
		}

		GameOver = CompleteSet(Animate(PLAYER, move - 1));
		if(!GameOver) {
			PlayersTurn = false;
		}
		return true;
	}

	std::cout << std::endl
		<< "Input not recognized." << std::endl
		<< std::endl;
	return false;
}

//---------------------------------------------------------------------------------+
// char GetChar                                                                    |
// Implemented to reduce redundant code, gets a single character from the user     |
//---------------------------------------------------------------------------------+
char GetChar(char Prompt[]) {
	char input;

	std::cout << Prompt;
	
	std::cin >> input;
	std::cin.ignore();
	
	return input;
}

//---------------------------------------------------------------------------------+
// bool isInt and int toInt                                                        |
// Small helper functions used in pair with GetChar for multi-type input           |
//---------------------------------------------------------------------------------+
bool isInt(char val) {
	int a = val - '0';
	return a >= 0 && a <= 9;
}
int toInt(char val) { return val - '0'; }
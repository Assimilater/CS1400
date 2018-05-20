//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 8: Recursion                                                         |
//---------------------------------------------------------------------------------+
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//---------------------------------------------------------------------------------+
// int CountCannonBalls - Task 1                                                   |
// Recursively count how many shells are in a square pyramid of height levels      |
//---------------------------------------------------------------------------------+
int CountCannonBalls(int levels) {
	if (levels == 1) { return 1; }
	return levels * levels + CountCannonBalls(levels - 1);
}

//---------------------------------------------------------------------------------+
// void PrintBinary - Task 2                                                       |
// Recursively print out an integer number in binary format                        |
//---------------------------------------------------------------------------------+
void PrintBinary(int num) {
	if (num < 2) {
		cout << num;
		return;
	}
	
	int bit = num % 2,
		divisor = num / 2;
	
	PrintBinary(divisor);
	cout << bit;
}

//---------------------------------------------------------------------------------+
// int ComputeSumOfDigits - Task 3                                                 |
// Recursively compute the sum of all digits in an integer number                  |
//---------------------------------------------------------------------------------+
int ComputeSumOfDigits(int num) {
	if (num < 10) {
		return num;
	}
	
	int digit = num % 10,
		divisor = num / 10;

	return digit + ComputeSumOfDigits(divisor);
}

//---------------------------------------------------------------------------------+
// Task 3 - Recursively solve a maze                                               |
// To solve this task I use a class to make the coordinate recursion read nicer    |
//---------------------------------------------------------------------------------+
class Coordinate {
private:
	static char** Maze;
	static int Rows, Cols;

	int Row, Col;
public:
	static enum Direction { UP, RIGHT, LEFT, DOWN };
	static void SetMaze(char** m, int r, int c) { Maze = m;  Rows = r; Cols = c; }

	Coordinate(int x = 0, int y = 0) { Row = x; Col = y; }

	//---------------------------------------------------------------------------------+
	// Coordinate MoveInDirection                                                      |
	// Alter the Row and Column of a Coordinate object for iterative purposes          |
	//---------------------------------------------------------------------------------+
	Coordinate MoveInDirection(Direction direction) {
		Coordinate destination(*this);
		switch (direction) {
		case UP:
			--destination.Row;
			break;
		case RIGHT:
			++destination.Col;
			break;
		case DOWN:
			++destination.Row;
			break;
		case LEFT:
			--destination.Col;
			break;
		}
		return destination;
	}

	//---------------------------------------------------------------------------------+
	// char GetMazeValue                                                               |
	// Return the value of the given maze at this coordinate                           |
	//---------------------------------------------------------------------------------+
	char GetMazeValue() {
		if (Row < Rows && Row >= 0 && Col < Cols && Col >= 0) {
			return Maze[Row][Col];
		}
		return 'X';
	}

	//---------------------------------------------------------------------------------+
	// char SetMazeValue                                                               |
	// Set the value of the given maze at this coordinate for tracking visited paths   |
	//---------------------------------------------------------------------------------+
	void SetMazeValue(char c) {
		// It is assumed that the program will only call this function for a valid coordinate
		Maze[Row][Col] = c;
	}

	//---------------------------------------------------------------------------------+
	// void PrintPath                                                                  |
	// Print the current position along a recursive path                               |
	//---------------------------------------------------------------------------------+
	void PrintPath(const bool isTreasure) {
		cout << (isTreasure ? "Treasure Found: " : "Treasure Paths: ") << Row << ", " << Col << endl;
	}
};

// Define static members of class Coordinate for compiler's sake
char** Coordinate::Maze;
int Coordinate::Rows, Coordinate::Cols;

//---------------------------------------------------------------------------------+
// bool SolveMaze                                                                  |
// Recursively find the treasure in the maze from a given position                 |
//---------------------------------------------------------------------------------+
bool SolveMaze(Coordinate Position) {
	if (Position.GetMazeValue() == 't') {
		Position.PrintPath(true);
		return true;
	}

	if (Position.GetMazeValue() == '.') {
		Position.SetMazeValue('+');

		// Use the resolution of the || operator to make a neat statement that will recursively check each point
		if (SolveMaze(Position.MoveInDirection(Coordinate::UP)) ||
			SolveMaze(Position.MoveInDirection(Coordinate::RIGHT)) ||
			SolveMaze(Position.MoveInDirection(Coordinate::DOWN)) ||
			SolveMaze(Position.MoveInDirection(Coordinate::LEFT))) {
			Position.PrintPath(false);
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------------------------------+
// void SetupMaze                                                                  |
// Read the maze.txt file, setup the Maze array, and trigger the recursive method  |
//---------------------------------------------------------------------------------+
void SetupMaze() {
	char** Maze;
	int Rows, Cols, sRow, sCol;

	// Read the file
	fstream fin("maze.txt", ios::in);
	fin >> Rows;
	fin >> Cols;
	fin >> sRow;
	fin >> sCol;

	// Fill the maze array with the data from the file
	Maze = new char*[Rows];
	for (int i = 0; i < Rows; ++i) {
		Maze[i] = new char[Cols];
		for (int j = 0; j < Cols; j++) {
			fin >> Maze[i][j];
			//cout << Maze[i][j];
		}
		//cout << endl;
	}

	Coordinate::SetMaze(Maze, Rows, Cols);

	// Solve the maze
	if (SolveMaze(Coordinate(sRow, sCol))) {
		cout << "Treasure FOUND! =)" << endl;
	}
	else {
		cout << "Treasure Not Found... =(" << endl;
	}

	// Clean up memory
	Coordinate::SetMaze(NULL, -1, -1);
	for (int i = 0; i < Rows; ++i) {
		delete[] Maze[i];
		Maze[i] = NULL;
	}
	delete[] Maze;
	Maze = NULL;
}

/** Below are four maze files I used to test the program
 * FILE 1
11 10
9 4
XXXXXXXXXX
XX...tX..X
XX.XXXX.XX
XX.......X
XXXXXXX.XX
X....XX.XX
X.XX.....X
X...XX.XXX
XXX..XXXXX
XXXX....XX
XXXXXXXXXX

 * FILE 2 (Solvable)
11 20
9 4
XXXXXXXXXXXXXXXXXXXX
XX...tX..X......X.XX
XX.XXXX.XX.X.X.XX.XX
XX.........XXXXX...X
XXXXXXX.XX.....X.X.X
X....XX.XX.XXX..X..X
X.XX..X..X....X.X.XX
X...X..XXXXXXXX.X..X
XXX..X....X...X.XX.X
XXXX..XXX...X......X
XXXXXXXXXXXXXXXXXXXX

 * FILE 3 (Unsolvable Version of FILE 2)
11 20
9 4
XXXXXXXXXXXXXXXXXXXX
XX...tX..X......X.XX
XX.XXXX.XX.X.X.XX.XX
XX.........XXXXX...X
XXXXXXX.XX..X..X.X.X
X....XX.XX.XXX..X..X
X.XX..X..X....X.X.XX
X...X..XXXXXXXX.X..X
XXX..X....X...X.XX.X
XXXX..XXX...X......X
XXXXXXXXXXXXXXXXXXXX

 * FILE 4 (Doubly-Solvable Version of FILE 2)
11 20
9 4
XXXXXXXXXXXXXXXXXXXX
XX...tX..X........XX
XX.XXXX.XX.X.X.XX.XX
XX.........XXXXX...X
XXXXXXX.XX.....X.X.X
X....XX.XX.XXX.....X
X.XX..X..X....X.X.XX
X...X..XXXXXXXX.X..X
XXX..X....X...XXXX.X
XXXX..XXX...X......X
XXXXXXXXXXXXXXXXXXXX

 */

int main() {
	const string SEPERATOR = "---------------------------------------------";
	
	// Task 1
	cout << SEPERATOR << endl << endl
		<< "Task 1 - Count Cannon Balls" << endl << endl;

	cout << "5  Levels: " << CountCannonBalls(5) << "  Shells" << endl;
	cout << "10 Levels: " << CountCannonBalls(10) << " Shells" << endl;

	// Task 2
	cout << endl
		<< SEPERATOR << endl << endl
		<< "Task 2 - Print Binary Number" << endl << endl;

	cout << "300 in Binary is: ";
	PrintBinary(300);
	cout << endl;

	cout << "8   in Binary is: ";
	PrintBinary(8);
	cout << endl;

	cout << "5   in Binary is: ";
	PrintBinary(5);
	cout << endl;

	cout << "0   in Binary is: ";
	PrintBinary(0);
	cout << endl;
	
	// Task 3
	cout << endl
		<< SEPERATOR << endl << endl
		<< "Task 3 - Count Sum of Digits" << endl << endl;

	cout << "The sum of digits in   5   is: " << ComputeSumOfDigits(5) << endl;
	cout << "The sum of digits in 25503 is: " << ComputeSumOfDigits(25503) << endl;

	// Task 4
	cout << endl
		<< SEPERATOR << endl << endl
		<< "Task 4 - Solve a Maze" << endl << endl;

	SetupMaze();

	cout << endl
		<< SEPERATOR << endl << endl;

	system("pause");
	return 0;
}

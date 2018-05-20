#ifndef GAME_H
#define GAME_H
#include <string>

struct Cartesian {
	int Col = 0, Row = 0;
	Cartesian(int x, int y) {
		Col = x;
		Row = y;
	};
};

class Game {
// Members
private:
	static enum Angle {
		UP,
		UP_LEFT,
		LEFT,
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT,
		RIGHT,
		UP_RIGHT
	};
	const static char
		PLAYER = 'o',
		COMPUTER = 'x',
		EMPTY = ' ';

	const static int
		EXTRA_COLS = 3,
		EXTRA_ROWS = 2;

	char** Board;
	bool GameOver,
		PlayersTurn;
	int WinLength,
		Cols,
		Rows;

public:
	const static int
		MIN_SIZE = 3,
		MAX_SIZE = 6;
// Constructor and Destructor
	Game(int size);
	~Game();

// Methods
	bool Play();

private:
	char SpotValue(Cartesian spot);
	char SpotValue(Cartesian spot, char value);

	bool ColumnFull(int column);
	bool CompleteSet(Cartesian spot);

	int CountMatch(Cartesian spot, char opponent, Angle aDir);
	Cartesian Transform(Cartesian spot, Angle aDir);
	Angle Reverse(Angle aDir);

	void DrawBoard();
	void PrintCentered(std::string text);
	void DrawIdentifiers();

	Cartesian Animate(char opponent, int column);
	bool ExecuteInput(char input);
};
#endif
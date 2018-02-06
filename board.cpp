//lib includes
#include <iostream>
#include <string>
//project includes
#include "board.h"

//using
using std::cout;
using std::endl;
using std::string;

Board::Board() {
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			if(i == 1) {
				tiles_[i][j] = black;
			} else if(i == BOARDSIZE - 2) {
				tiles_[i][j] = white;
			} else {
			  tiles_[i][j] = none;
			}
		}
	}
}

Board::Board(int w, int b) : Board() {
	tiles_[BOARDSIZE - 2][w - 1] = none;
	tiles_[1][b - 1] = none;
}

std::ostream& operator<< (std::ostream &out, Board const& board) {
	string alphabet = "   A B C D E F G H   ";
	cout << alphabet << endl;

	for (int i = 0; i < BOARDSIZE; ++i) {
		cout << BOARDSIZE - i << "  ";
		for (int j =  0; j < BOARDSIZE; ++j) {
			if (board.is_black(i, j)) {
				cout << BLACKPAWN;
			} else if (board.is_white(i, j)) {
				cout << WHITEPAWN;
			} else if (board.is_empty(i, j)) {
				cout << '.';
			} else {
				cout << ' ';
			}
			cout << ' ';
		}
		cout << " " << BOARDSIZE - i << endl;
	}

	cout << alphabet << endl;

	return out;
}

tile Board::won() const {
	if (number_of_pawns(black) == 0 && number_of_pawns(white) > 0)
	{
		return white;
	}

	if (number_of_pawns(black) > 0 && number_of_pawns(white) == 0) {
		return black;
	}

	return none;
}

int Board::number_of_pawns(tile p) const {
	int sum = 0;
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		for (int j = 0; j < BOARDSIZE; ++j)
		{
			sum = tiles_[i][j] == p ? sum + 1 : sum;
		}
	}

	return sum;
}
#ifndef BOARD_H
#define BOARD_H

//lib includes
#include <iostream>
//project includes
#include "general_header.h"
#include "tile.h"

class Board {
	private:
		tile tiles_[8][8];
	public:
		bool is_black(int i, int j) const { return tiles_[i][j] == black; }
		bool is_white(int i, int j) const { return tiles_[i][j] == white; }
		bool is_empty(int i, int j) const { return tiles_[i][j] == none; }
		Board();
		Board(int w, int b);
		friend std::ostream& operator<< (std::ostream &out, Board const& board);		
		tile won() const;
		int number_of_pawns(tile p) const;
};



#endif
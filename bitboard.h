#ifndef BITBOARD_H
#define BITBOARD_H

//libs includes
#include <iostream>
#include <utility>

//project includes
#include "board.h"
#include "tile.h"

typedef std::pair<int, int> pair_ii;

void getll(unsigned long long & white, unsigned long long & black, unsigned long long & en_pass, Board board);
unsigned long long allmoves(unsigned long long black, unsigned long long white, unsigned long long en_pass, tile player, movetype mov);
unsigned long long coor_to_bits(int i, int j);
pair_ii bits_to_coor(unsigned long long a);


#endif
#ifndef BITBOARD_H
#define BITBOARD_H

//libs includes
#include <iostream>
#include <utility>

//project includes
#include "board.h"
#include "tile.h"

void getll(long long & white, long long & black, long long & en_pass, Board board);
long long allmoves(long long black, long long white, long long en_pass, tile player, movetype mov);
long long coor_to_bits(int i, int j);
pair<int, int> bits_to_coor(long long a);


#endif
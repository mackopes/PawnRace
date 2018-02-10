#include "bitboard.h"


//helper functions

//get all possible moves of attacker (direction of attacker is south, bithsift right)
long long move_fwd_helper(long long attacker, long long deffender, long long en_pass) {
  return (attacker >> 8) & (~ deffender);
}

long long rev_bites(long long side) {  //may be faster
  long long count = sizeof(side) * 8 - 1;
  long long reverse_side = side;

  side >>= 1;
  while (side) {
    reverse_side <<= 1;
    reverse_side |= side & 1;
    side >>= 1;
    count--;
  }
  reverse_num <<= count;
  return reverse_num;
}

//public functions

long long allmoves(long long black, long long white, long long en_pass, tile player, movetype mov) {
  long long (*move_function)(long long, long long, long long);
  switch (move) {
  case fwd:
    move_function = &move_fwd_helper;
    break;
  default:
    move_function = &move_fwd_helper;
    break;
  }

  if (player == black) {
    return (*move_function)(black, white, en_pass);
  } else if (player == white) {
    return rev_bites((*move_function)(rev_bites(white), rev_bites(black), rev_bites(en_pass)));
  } else {
    return 0;
  }
}

long long coor_to_bits(int i, int j) {
  return (1L << (i * 8 + j));
}

pair<int, int> bits_to_coor(long long a) {
  return std::makepair(a / 8, a & 8);
}



void getll(long long & white, long long & black, long long & en_pass, Board board) {
  white = black = en_pass = 0;

  for (int i = 0; i < BOARDSIZE; ++i) {
    for (int j = 0; j < BOARDSIZE; ++j) {
      if (board.is_white(i, j)) {
        white |= coor_to_bits(i, j);
      } else if (board.is_black(i, j)) {
        black |= coor_to_bits(i, j);
      } else if (board.is_en_pass(i, j)) {
        en_pass |= coor_to_bits(i, j);
      }
    }
  }
}
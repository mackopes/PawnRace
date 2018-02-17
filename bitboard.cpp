#include "bitboard.h"


//helper functions

//get all possible moves of attacker (direction of attacker is south, bithsift right)
unsigned long long move_fwd_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  return ( (attacker << 8) & (~(deffender | attacker)) );
}

unsigned long long move_ffwd_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  return ( (attacker << 16) & ( ~(deffender | attacker | (attacker << 8) | (deffender << 8)) & (0xFFUL << 24) ) );  //0xFF is mask for first row of attacker
}

unsigned long long move_capt_r_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  //0x8080808080808080 is mask for the leftmost collumn from attackers view, and he can't end here
  return ( (attacker << 7) & (deffender & (~0x8080808080808080UL)) ); //7 is right
}

unsigned long long move_capt_l_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  //0x1010101010101010 is mask for the rightmost collumn from attackers view, and he can't end here
  return ( (attacker << 9) & (deffender & (~0x0101010101010101UL)) ); //9 is left
}

unsigned long long move_capt_pass_r_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  return ( (attacker << 7) & (en_pass & (~0x8080808080808080UL)));
}

unsigned long long move_capt_pass_l_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  return ( (attacker << 9) & (en_pass & (~0x0101010101010101UL)));
}

unsigned long long move_empty_helper(unsigned long long attacker, unsigned long long deffender, unsigned long long en_pass) {
  return 0L; //empty
}

unsigned long long rev_bites(unsigned long long side) {  //may be faster
  unsigned long long output = side;
  for (int i = sizeof(side) * 8 - 1; i; --i) {
    output <<= 1L;
    side >>= 1L;
    output |=  side & 1L;
  }
  return output;
}

//public functions

unsigned long long allmoves(unsigned long long bl, unsigned long long wh, unsigned long long ep, tile player, movetype mov) {
  unsigned long long (*move_function)(unsigned long long, unsigned long long, unsigned long long);
  switch (mov) {
  case fwd:
    move_function = &move_fwd_helper;
    break;
  case ffwd:
    move_function = &move_ffwd_helper;
    break;
  case capt_r:
    move_function = &move_capt_r_helper;
    break;
  case capt_l:
    move_function = &move_capt_l_helper;
    break;
  case captpass_r:
    move_function = &move_capt_pass_r_helper;
    break;
  case captpass_l:
    move_function = &move_capt_pass_l_helper;
    break;
  default:
    std::cerr << "unkown move in function allmoves" << std::endl;
    move_function = &move_empty_helper;
    break;
  }

  if (player == black) {
    return (*move_function)(bl, wh, ep);
  } else if (player == white) {
    return rev_bites((*move_function)(rev_bites(wh), rev_bites(bl), rev_bites(ep)));
  } else {
    return 0;
  }
}

unsigned long long coor_to_bits(int i, int j) {
  return (1L << (i * 8 + j));
}

pair_ii bits_to_coor(unsigned long long a) {
  for (int i = 0; i < 64; ++i) {
    if (a & (1L << i)) {
      return std::make_pair(i / 8, i % 8);
      break;
    }
  }

}



void getll(unsigned long long & white, unsigned long long & black, unsigned long long & en_pass, Board board) {
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
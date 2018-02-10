#include "random_player.h"

#define ENUMEND fwd
#define ENUMSTART fwd

Move Random_Player :: get_move(Board board) {
  long long white, black, en_pass;

  //void getll(long long & white, long long & black, long long & en_pass, Board board);
  getll(white, black, en_pass, board);

  //long long allmoves(long long black, long long white, long long en_pass, tile player, movetype mov);

  std::vector <long long> move_ll;
  move_ll.resize(ENUMEND - ENUMSTART);
  for (int i = ENUMSTART; i <= ENUMEND; ++i) {
    move_ll[i] = allmoves(black, white, en_pass, color(), i);
  }

  return random_element(get_all_possible_moves(move_ll));

}

int random_int(int min, int max) {
  return rand() % (max - min + 1) + min;
}

template<class T>
T Random_Player :: random_element(std::vector<T> &elements) {
  return elements[random_int(0, elements.size() - 1)];
}
}

vector <Move> Random_Player :: get_all_possible_moves(vector<long long> & move_ll) {
  int direction = color() == white ? WHITEDIR : BLACKDIR;
  vector <Move> mv;
  for (int i = 0; i < move_ll.size(); ++i) {
    for (int j = 0; j < 64; ++j) {
      long long pos = move_ll[i] & (1 << j);
      if (pos) {
        switch (i) {
        case fwd:
          long long orig_pos = color() == black ? pos << 8 : pos >> 8;
          //Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant);
          mv.push_back(Move(color(), coor_to_bits(orig_pos), coor_to_bits(pos), false, false));
          break;
        case ffwd:
        default:
          break;
        }
      }
    }
  }

  return mv;

}
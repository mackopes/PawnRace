#include "random_player.h"

#define ENUMEND captpass_l
#define ENUMSTART fwd

Random_Player :: Random_Player(tile color) : Player(color) {
  timeval t1;
  gettimeofday(&t1, NULL);
  seed_ = t1.tv_sec * t1.tv_usec;
  srand(seed_);
}

Random_Player :: Random_Player(tile color, long seed) : Player(color) {
  seed_ = seed;
  srand(seed_);
}

Move Random_Player :: get_move(Board board) {
  unsigned long long white, black, en_pass;

  //void getll(unsigned long long & white, unsigned long long & black, unsigned long long & en_pass, Board board);
  getll(white, black, en_pass, board);

  //unsigned long long allmoves(unsigned long long black, unsigned long long white, unsigned long long en_pass, tile player, movetype mov);

  std::vector <unsigned long long> move_ll;
  move_ll.resize(ENUMEND - ENUMSTART + 1);
  for (int i = ENUMSTART; i <= ENUMEND; ++i) {
    movetype mt = static_cast<movetype>(i);
    move_ll[i] = allmoves(black, white, en_pass, color(), mt);
  }

  std::vector<Move> all_moves = get_all_possible_moves(move_ll);
  if (all_moves.empty()) {
    //Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant, bool no_move = false);
    return Move(color(), std::make_pair(-1, -1), std::make_pair(-1, -1), false, false, true);
  } else {
    return random_element(all_moves);
  }
}

int Random_Player :: random_int(int min, int max) {
  return ((rand() % (max - min + 1)) + min);
}

template<class T>
T Random_Player :: random_element(std::vector<T> &elements) {
  return elements[random_int(0, elements.size() - 1)];
}

std::vector <Move> Random_Player :: get_all_possible_moves(std::vector<unsigned long long> move_ll) {
  std::vector <Move> mv;
  for (int i = 0; i < move_ll.size(); ++i) {
    for (int j = 0; j < 64; ++j) {
      unsigned long long pos = move_ll[i] & (1L << j);
      if (pos) {
        //Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant);
        //enum movetype {fwd, ffwd, capt_r, capt_l, captpass_r, captpass_l};
        switch (static_cast<movetype>(i)) {
        case fwd: {
          unsigned long long orig_pos = (color() == black ? pos >> 8 : pos << 8);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), false, false));
        }
        break;
        case ffwd: {
          unsigned long long orig_pos = (color() == black ? pos >> 16 : pos << 16);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), false, true));
        }
        break;
        case capt_r: {
          unsigned long long orig_pos = (color() == black ? pos >> 7 : pos << 7);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), true, false));
        }
        break;
        case capt_l: {
          unsigned long long orig_pos = (color() == black ? pos >> 9 : pos << 9);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), true, false));
        }
        break;
        case captpass_r: {
          unsigned long long orig_pos = (color() == black ? pos >> 7 : pos << 7);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), true, true));
        }
        break;
        case captpass_l: {
          unsigned long long orig_pos = (color() == black ? pos >> 9 : pos << 9);
          mv.push_back(Move(color(), bits_to_coor(orig_pos), bits_to_coor(pos), true, true));
        }
        break;
        default:
          break;
        }
      }
    }
  }

  return mv;

}

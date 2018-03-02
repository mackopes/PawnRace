#include "minimax_player.h"

#define ALPHA 0
#define BETA 0

Minimax_Player :: Minimax_Player(tile color) : Player(color) {
  //empty
}

Move Minimax_Player :: get_move(Board board) {
  unsigned long long w, b, ep;

  //convert the board to longlongs
  //void getll(unsigned long long & w, unsigned long long & b, unsigned long long & ep, Board board);
  getll(w, b, ep, board);

  //double minimax(ll attacker, ll deffender, ll ep, double & alpha, double & beta, ll & best_move, int current_depth, int max_depth, double carry)
  Move best_move;
  ll alpha = ALPHA, beta = BETA;
  if (color() == black) {
    /* start minimax without swapping the b/w players */
    std::cout << minimax(b, w, ep, ALPHA, BETA, best_move, 0, 6, 0) << std::endl;
  } else {
    /* start minimax with swapping the b/w players */
    std::cout << minimax(rev_bites(w), rev_bites(b), rev_bites(ep), ALPHA, BETA, best_move, 0, 7, 0) << std::endl;
  }

  return best_move;
}

double Minimax_Player :: eval(ll attacker, ll deffender) {
  double att = 0;
  double def = 0;

  while (attacker > 0) {
    att += (attacker & 1);
    attacker = attacker >> 1;
  }

  while (deffender > 0) {
    def += (deffender & 1);
    deffender = deffender >> 1;
  }

  return att / def;
}

double Minimax_Player :: minimax_helper(ll attacker, ll deffender, ll ep, double alpha, double beta, ll & best_move, int current_depth, int max_depth, double carry, movetype mov) {
  ll moves;
  double best_score = DBLMIN;
  bool move_made = false;
  ll new_att, new_def, new_ep, buff;

  moves = allmoves(attacker, deffender, ep, mov);
  for (int i = 0; i < 64; ++i) {
    buff = moves & (1UL << i);
    if (buff) {
      move_made = true;
      double bs;
      switch (mov) {
      case fwd:
        new_att = (attacker | buff) & (~(buff >> 8));
        new_def = deffender;
        new_ep = 0;
        break;
      case capt_r:
        new_att = (attacker | buff) & (~(buff >> 7));
        new_def = (deffender & (~buff));
        new_ep = 0;
        break;
      case capt_l:
        new_att = (attacker | buff) & (~(buff >> 9));
        new_def = (deffender & (~buff));
        new_ep = 0;
        break;
      default:
        std :: cout << "unknown move!" << std :: endl;
        break;
      }
      Move dummy;
      bs = minimax(rev_bites(new_def), rev_bites(new_att), new_ep, ALPHA, BETA, dummy, current_depth + 1, max_depth, carry);
      if (bs > best_score) {
        best_score = bs;
        best_move = buff;
      }
    }
  }

  if (!move_made) {
    best_move = 0;
    return 0;
  }

  return best_score;
}

/*
 * attacker has to be moving like black player does (x-coordinate is increasing).
 * every level deeper attacker and deffender have to swap
 * best_move stores the best played move
 */
double Minimax_Player :: minimax(ll attacker, ll deffender, ll ep, double alpha, double beta, Move & best_move, int current_depth, int max_depth, double carry) {
  if (current_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(attacker, deffender);
  }

  double best_score = DBLMIN;
  ll bm;

  ll bs;
  for (movetype m : {fwd, capt_r, capt_l}) {
    bs = minimax_helper(attacker, deffender, ep, alpha, beta, bm, current_depth, max_depth, carry, m);
    if (bs > best_score) {
      std :: cout << "macka\n";
      ll orig_pos;
      if (color() == white) {
        bm = rev_bites(bm);
      }
      switch (m) {
      case fwd:
        orig_pos = (color() == black ? bm >> 8 : bm << 8);
        best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), false, false);
        break;
      case capt_r:
        orig_pos = (color() == black ? bm >> 7 : bm << 7);
        best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
        break;
      case capt_l:
        orig_pos = (color() == black ? bm >> 9 : bm << 9);
        best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
        break;
      }
      best_score = bs;
    }
  }

  return best_score;
}
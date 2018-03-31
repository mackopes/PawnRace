#include "minimax_player.h"

#define ALPHA 0
#define BETA 0
#define MAXDEPTH 5

Minimax_Player :: Minimax_Player(tile color) : Player(color) {
  //empty
}

Move Minimax_Player :: get_move(Board board) {
  ll w, b, ep;

  //convert the board to longlongs
  //void getll(unsigned long long & w, unsigned long long & b, unsigned long long & ep, Board board);
  getll(w, b, ep, board);

  //double minimax(ll attacker, ll deffender, ll ep, double & alpha, double & beta, ll & best_move, int current_depth, int max_depth, double carry)
  Move best_move;
  ll alpha = ALPHA, beta = BETA;
  if (color() == black) {
    /* start minimax without swapping the b/w players */
    std::cout << minimax(b, w, ep, ALPHA, BETA, best_move, 0, MAXDEPTH, true, 0) << std::endl;
  } else {
    /* start minimax with swapping the b/w players */
    std::cout << minimax(rev_bites(w), rev_bites(b), rev_bites(ep), ALPHA, BETA, best_move, 0, MAXDEPTH, true, 0) << std::endl;
  }

  return best_move;
}

//May use templates here
bool Minimax_Player :: is_greater(double a, double b) {
  return a > b;
}

bool Minimax_Player :: is_smaller(double a, double b) {
  return a < b;
}

double Minimax_Player :: eval(ll attacker, ll deffender, bool maximizing) {
  double att = 0;
  double def = 0;
  int multiplier = 1;
  int multiplier_changer = 1;
  int rowcount = 0;
  while (attacker > 0) {
    att += (attacker & 1UL)*multiplier;
    attacker = attacker >> 1;
    if(++rowcount >= 7) {
      multiplier += multiplier_changer++;
      rowcount = 0;
    }
  }

  multiplier = 36;
  multiplier_changer = 8;
  rowcount = 0;
  while (deffender > 0) {
    def += (deffender & 1UL)*multiplier;
    deffender = deffender >> 1;
    if(++rowcount >= 7){
      multiplier -= multiplier_changer--;
      rowcount = 0;
    }
  }

  /* Better score for better def position
   * def was attacker turn before evaluation
  */

  // std::cout << "def " << def << " att " << att << std::endl;
  if (maximizing)
  {
    return def - att;
  } else {
    return att - def;
  }
  
}

double Minimax_Player :: minimax_helper(ll attacker, ll deffender, ll ep, double alpha, double beta, ll & best_move, int current_depth, int max_depth, bool maximizing, double carry, movetype mov) {
  ll moves;
  double best_score = maximizing ? DBLMIN : DBLMAX;
  bool move_made = false;
  ll new_att, new_def, new_ep, buff;

  bool (*cmp_fnction)(double, double) = (maximizing ? is_greater : is_smaller);

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
      bs = minimax(rev_bites(new_def), rev_bites(new_att), new_ep, ALPHA, BETA, dummy, current_depth + 1, max_depth, !maximizing, carry);
      if ((*cmp_fnction)(bs, best_score)) {
        best_score = bs;
        best_move = buff;
      }
    }
  }

  return best_score;
}

/*
 * attacker has to be moving like black player does (x-coordinate is increasing).
 * every level deeper attacker and deffender have to swap
 * best_move stores the best played move
 */
double Minimax_Player :: minimax(ll attacker, ll deffender, ll ep, double alpha, double beta, Move & best_move, int current_depth, int max_depth, bool maximizing, double carry) {
  if (current_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(attacker, deffender, maximizing);
  }
  
  //std:: cout << "depth: " << current_depth << std::endl;
  double best_score = maximizing ? DBLMIN : DBLMAX;
  ll bm;

  double bs;
  bool (*cmp_fnction)(double, double) = (maximizing ? is_greater : is_smaller);
  for (movetype m : {fwd, capt_r, capt_l}) {
    bs = minimax_helper(attacker, deffender, ep, alpha, beta, bm, current_depth, max_depth, maximizing, carry, m);
    if ((*cmp_fnction)(bs, best_score)) {
      ll orig_pos;
      if (color() == white) {
        bm = rev_bites(bm);
      }
      switch (m) {
        case fwd:
          // std:: cout<< "fwdbs " << bs << std::endl;
          orig_pos = (color() == black ? bm >> 8 : bm << 8);
          best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), false, false);
          break;
        case capt_r:
          // if (current_depth ==0) {
          //   std :: cout << "capt_r " << bites(bm) << std::endl;
          // }
          // std:: cout<< "rbs " << bs << std::endl;
          orig_pos = (color() == black ? bm >> 7 : bm << 7);
          best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
          break;
        case capt_l:
          // if (current_depth == 0) {
          //   std :: cout << "capt_l " << bites(bm) << std::endl;
          // }
          // std:: cout<< "lbs " << bs << std::endl;
          orig_pos = (color() == black ? bm >> 9 : bm << 9);
          best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
          break;
        default:
          break;
        }
      best_score = bs;
    }
  }
  return best_score;
}

#include "minimax_player.h"

#define MAXDEPTH 8
#define ALLOWEDMOVES {fwd}

using std::max;
using std::min;

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
  if (color() == black) {
    /* start minimax without swapping the b/w players */
    return minimax(b, w, ep);
  } else {
    /* start minimax with swapping the b/w players */
    return minimax(rev_bites(w), rev_bites(b), rev_bites(ep));
  }
}


/* NOT FINISHED
 * TODO: iterative deepening based on time
 */
Move Minimax_Player :: minimax(ll attacker, ll deffender, ll ep) {
  return minimax_start(attacker, deffender, ep, MAXDEPTH);
}

Move Minimax_Player :: minimax_start(ll attacker, ll deffender, ll ep, int max_depth) {
  //initialize alpha and beta
  double alpha = DBLMIN;
  double beta = DBLMAX;

  //start is always maximizing player
  //behaves like alpha-beta maximizing, but return best move instead of best score
  Move best_move = Move();
  double best_score = DBLMIN;
  for (movetype move : ALLOWEDMOVES) {
    //get all the moves we can make of certain movetype
    ll moves = allmoves(attacker, deffender, ep, move);
    //iterate over all moves of certain movetype
    for (int i = 0; i < 64; ++i) {
      ll buff = moves & (1UL << i);
      ll new_att, new_def, new_ep;
      if (buff) {
        //get new positions of attacker and deffender after the move made
        switch (move) {
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

        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MAXIMUM in minimizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_minimizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), 1, max_depth, alpha, beta);
        //update best_score and alpha
        if (bs > best_score)
        {
          best_score = bs;
          //Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant, bool no_move = false);
          switch (move) {
            case fwd:
              best_move = Move(color(), bits_to_coor(buff >> 8), bits_to_coor(buff), false, false);
              break;
            default:
              break;
          }
        }
        alpha = max(alpha, best_score);
        //alpha-beta cutoff
        if (beta < alpha) {
          break;
        }
      }
    }
    //alpha-beta cutoff again
    if (beta < alpha) {
      break;
    }
  }

  std::cout << best_score << std::endl;
  
  return best_move;
}

double Minimax_Player :: alphabeta_maximizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta) {
  if (cur_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(rev_bites(deffender), rev_bites(attacker));
  }

  double best_score = DBLMIN;
  for (movetype move : ALLOWEDMOVES) {
    //get all the moves we can make of certain movetype
    ll moves = allmoves(attacker, deffender, ep, move);
    //iterate over all moves of certain movetype
    for (int i = 0; i < 64; ++i) {
      ll buff = moves & (1UL << i);
      ll new_att, new_def, new_ep;
      if (buff) {
        //get new positions of attacker and deffender after the move made
        switch (move) {
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

        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MAXIMUM in minimizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_minimizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), cur_depth + 1, max_depth, alpha, beta);
        //update best_score and alpha
        best_score = max(best_score, bs);
        alpha = max(alpha, best_score);
        //alpha-beta cutoff
        if (beta < alpha) {
          break;
        }
      }
    }
    //alpha-beta cutoff again
    if (beta < alpha) {
      break;
    }
  }

  return best_score;
}

double Minimax_Player :: alphabeta_minimizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta) {
  if (cur_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(attacker, deffender);
  }

  double best_score = DBLMAX;
  for (movetype move : ALLOWEDMOVES) {
    //get all the moves we can make of certain movetype
    ll moves = allmoves(attacker, deffender, ep, move);
    //iterate over all moves of certain movetype
    for (int i = 0; i < 64; ++i) {
      ll buff = moves & (1UL << i);
      ll new_att, new_def, new_ep;
      if (buff) {
        //get new positions of attacker and deffender after the move made
        switch (move) {
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
        
        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MINIMUM in maximizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_maximizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), cur_depth + 1, max_depth, alpha, beta);
        //update best_score and beta
        best_score = min(best_score, bs);
        beta = min(beta, best_score);
        //alpha-beta cutoff
        if (beta < alpha) {
          break;
        }
      }
    }
    //alpha-beta cutoff again
    if (beta < alpha) {
      break;
    }
  }

  return best_score;
}

/* General eval, calling all other evals */
double Minimax_Player :: eval (ll attacker, ll deffender) {
  return eval_positions(attacker, deffender);
}

double Minimax_Player :: eval_positions(ll attacker, ll deffender) {
  double att = 0;
  double def = 0;
  int multiplier = 1;
  int rowcount = 0;
  while (attacker > 0) {
    att += (attacker & 1UL)*multiplier;
    attacker = attacker >> 1;
    if(++rowcount >= 7) {
      multiplier *= 2;
      if (multiplier == 128)
      {
        multiplier = 1024;
      }
      rowcount = 0;
    }
  }

  multiplier = 1024;
  rowcount = 0;
  while (deffender > 0) {
    def += (deffender & 1UL)*multiplier;
    deffender = deffender >> 1;
    if(++rowcount >= 7){
      multiplier /= 2;
      if (multiplier == 512)
      {
        multiplier = 64;
      }
      rowcount = 0;
    }
  }

  return def - att;
}


// double Minimax_Player :: minimax_helper(ll attacker, ll deffender, ll ep, double alpha, double beta, ll & best_move, int current_depth, int max_depth, bool maximizing, double carry, movetype mov) {
//   ll moves;
//   double best_score = maximizing ? DBLMIN : DBLMAX;
//   bool move_made = false;
//   ll new_att, new_def, new_ep, buff;

//   bool (*cmp_fnction)(double, double) = (maximizing ? is_greater : is_smaller);

//   moves = allmoves(attacker, deffender, ep, mov);
//   for (int i = 0; i < 64; ++i) {
//     buff = moves & (1UL << i);
//     if (buff) {
//       move_made = true;
//       double bs;
//       switch (mov) {
//       case fwd:
//         new_att = (attacker | buff) & (~(buff >> 8));
//         new_def = deffender;
//         new_ep = 0;
//         break;
//       case capt_r:
//         new_att = (attacker | buff) & (~(buff >> 7));
//         new_def = (deffender & (~buff));
//         new_ep = 0;
//         break;
//       case capt_l:
//         new_att = (attacker | buff) & (~(buff >> 9));
//         new_def = (deffender & (~buff));
//         new_ep = 0;
//         break;
//       default:
//         std :: cout << "unknown move!" << std :: endl;
//         break;
//       }
//       Move dummy;
//       bs = minimax(rev_bites(new_def), rev_bites(new_att), new_ep, alpha, beta, dummy, current_depth + 1, max_depth, !maximizing, carry);
//       if ((*cmp_fnction)(bs, best_score)) {
//         best_score = bs;
//         best_move = buff;

//         if (maximizing) {
//           alpha = std::max(alpha, bs);
//         } else {
//           beta = std::min(beta, bs);
//         }

//         if (beta <= alpha)
//         {
//           break;
//         }
//       }
//     }
//   }

//   return best_score;
// }

// /*
//  * attacker has to be moving like black player does (x-coordinate is increasing).
//  * every level deeper attacker and deffender have to swap
//  * best_move stores the best played move
//  */
// double Minimax_Player :: minimax(ll attacker, ll deffender, ll ep, double alpha, double beta, Move & best_move, int current_depth, int max_depth, bool maximizing, double carry) {
//   if (current_depth >= max_depth || has_ended(attacker, deffender)) {
//     return eval(attacker, deffender, maximizing);
//   }
  
//   //std:: cout << "depth: " << current_depth << std::endl;
//   double best_score = maximizing ? DBLMIN : DBLMAX;
//   ll bm;

//   double bs;
//   bool (*cmp_fnction)(double, double) = (maximizing ? is_greater : is_smaller);
//   for (movetype m : {fwd, capt_r, capt_l}) {
//     bs = minimax_helper(attacker, deffender, ep, alpha, beta, bm, current_depth, max_depth, maximizing, carry, m);
//     if (current_depth == 0)
//     {
//       std::cout << bs << std::endl;
//     }
//     if ((*cmp_fnction)(bs, best_score)) {
//       ll orig_pos;
//       //alpha-beta pruning
//       if (color() == white) {
//         bm = rev_bites(bm);
//       }
//       switch (m) {
//         case fwd:
//           // if (current_depth == 0) {
//           //   std:: cout<< "fwdbs " << bs << std::endl;
//           // }
//           orig_pos = (color() == black ? bm >> 8 : bm << 8);
//           best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), false, false);
//           break;
//         case capt_r:
//           // if (current_depth ==0) {
//           //   std :: cout << "capt_r " << bites(bm) << std::endl;
//           // }
//           // if (current_depth == 0) {
//           //   std:: cout<< "rbs " << bs << std::endl;
//           // }
//           orig_pos = (color() == black ? bm >> 7 : bm << 7);
//           best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
//           break;
//         case capt_l:
//           // if (current_depth == 0) {
//           //   std :: cout << "capt_l " << bites(bm) << std::endl;
//           // }
//           // if (current_depth == 0) {
//           //   std:: cout<< "lbs " << bs << std::endl;
//           // }
//           orig_pos = (color() == black ? bm >> 9 : bm << 9);
//           best_move = Move(color(), bits_to_coor(orig_pos), bits_to_coor(bm), true, false);
//           break;
//         default:
//           break;
//         }
//       best_score = bs;
//     }
//   }
//   return best_score;
// }

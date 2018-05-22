#include "minimax_player.h"

#define STARTDEPTH 8
#define ALLOWEDMOVES {captpass_r, captpass_l, capt_r, capt_l, ffwd, fwd}
#define DRAW_SCORE 0.5
#define DEPTH_THRESHOLD 6

using std::max;
using std::min;

Minimax_Player::Minimax_Player(tile color) : Player(color) {
  max_time_ = 5000;
  set_timer();
  timeout_flag_ = false;
  boardhash.clear();
}

Minimax_Player::Minimax_Player(tile color, long max_time) : Player(color) {
  max_time_ = max_time;
  set_timer();
  timeout_flag_ = false;
  boardhash.clear();
}

Move Minimax_Player::get_move(Board board) {
  ll w, b, ep;
  best_eval_ = 0;
  //convert the board to longlongs
  //void getll(ll & w, ll & b, ll & ep, Board board);
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

/* Set the timer */
void Minimax_Player::set_timer() {
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time_);
}

/* Ckeck if ran out of time (given by max_time_) */
bool Minimax_Player::timeout() {
  struct timespec stop;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &stop);
  long t = (stop.tv_sec - start_time_.tv_sec) * 1000 + (stop.tv_nsec - start_time_.tv_nsec) / 1000000;
  return t >= max_time_;
}

Move Minimax_Player::minimax(ll attacker, ll deffender, ll ep) {
  int depth = STARTDEPTH;
  Move m;
  timeout_flag_ = false;
  set_timer();
    
  do{
    depth_reached_ = 0;
    Move m_ = minimax_start(attacker, deffender, ep, depth);
    if (!timeout_flag_) {
      m = m_;
      depth++;
    }
  } while (!timeout() && depth_reached_ >= depth - 1);

  if(get_print()) {
    std::cout << "Score: " << best_eval_ << std::endl;
    std::cout << "Depth reached: " << depth - 1 << std::endl;
  }
  return m;
}

/* get new positions of attacker, deffender and ep after given move is made */
void Minimax_Player::get_next_position(movetype movtp, ll move, ll attacker, ll deffender, ll ep, ll & new_att, ll & new_def, ll & new_ep) {
  switch (movtp) {
  case fwd:
    new_att = (attacker | move) & (~(move >> 8));
    new_def = deffender;
    new_ep = 0;
    break;
  case capt_r:
    new_att = (attacker | move) & (~(move >> 7));
    new_def = (deffender & (~move));
    new_ep = 0;
    break;
  case capt_l:
    new_att = (attacker | move) & (~(move >> 9));
    new_def = (deffender & (~move));
    new_ep = 0;
    break;
  case ffwd:
    new_att = (attacker | move) & (~(move >> 16));
    new_def = deffender;
    new_ep = move >> 8;
    break;
  case captpass_r:
    new_att = (attacker | move) & (~(move >> 7));
    new_def = (deffender & (~(move << 8)));
    new_ep = 0;
    break;
  case captpass_l:
    new_att = (attacker | move) & (~(move >> 9));
    new_def = (deffender & (~(move << 8)));
    new_ep = 0;
    break;
  default:
    std::cout << "unknown move!" << std::endl;
    break;
  }
}

/* translate move from ll to Move */
Move Minimax_Player::translate_move(ll move, movetype movtp) {
  if (color() == black) {
    switch (movtp) {
    case fwd:
      return Move(color(), bits_to_coor(move >> 8), bits_to_coor(move), false, false);
      break;
    case capt_r:
      return Move(color(), bits_to_coor(move >> 7), bits_to_coor(move), true, false);
      break;
    case capt_l:
      return Move(color(), bits_to_coor(move >> 9), bits_to_coor(move), true, false);
      break;
    case ffwd:
      return Move(color(), bits_to_coor(move >> 16), bits_to_coor(move), false, true);
      break;
    case captpass_r:
      return Move(color(), bits_to_coor(move >> 7), bits_to_coor(move), true, true);
      break;
    case captpass_l:
      return Move(color(), bits_to_coor(move >> 9), bits_to_coor(move), true, true);
      break;
    default:
      std::cerr << "unknown move in translate_move\n";
      return Move();
      break;
    }
  } else {
    move = rev_bites(move);
    switch (movtp) {
    case fwd:
      return Move(color(), bits_to_coor(move << 8), bits_to_coor(move), false, false);
      break;
    case capt_r:
      return Move(color(), bits_to_coor(move << 7), bits_to_coor(move), true, false);
      break;
    case capt_l:
      return Move(color(), bits_to_coor(move << 9), bits_to_coor(move), true, false);
      break;
    case ffwd:
      return Move(color(), bits_to_coor(move << 16), bits_to_coor(move), false, true);
      break;
    case captpass_r:
      return Move(color(), bits_to_coor(move << 7), bits_to_coor(move), true, true);
      break;
    case captpass_l:
      return Move(color(), bits_to_coor(move << 9), bits_to_coor(move), true, true);
      break;
    default:
      std::cerr << "unknown move in translate_move\n";
      return Move();
      break;
    }
  }

}

/* place to start minimax algorithm
 * initializes variables and start alphabeta
 * get best value from alphabeta and returns coresponding move
 */
Move Minimax_Player::minimax_start(ll attacker, ll deffender, ll ep, int max_depth) {
  //initialize alpha and beta
  double alpha = DBLMIN;
  double beta = DBLMAX;
  //clear hashmap
  boardhash.clear();

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
        get_next_position(move, buff, attacker, deffender, ep, new_att, new_def, new_ep);

        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MAXIMUM in minimizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_minimizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), 1, max_depth, alpha, beta);
        //update best_score and alpha
        if (bs > best_score) {
          best_score = bs;
          best_move = translate_move(buff, move);
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

  best_eval_ = best_score > best_eval_ ? best_score : best_eval_;

  return best_move;
}

/* maximizing player in alphabeta algorithm */
double Minimax_Player::alphabeta_maximizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta) {
  if (max_depth != STARTDEPTH && (timeout() || timeout_flag_)) {
    timeout_flag_ = true;
    return -1;
  }

  depth_reached_ = depth_reached_ < cur_depth ? cur_depth : depth_reached_;

  if (cur_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(attacker, deffender, cur_depth);
  }

  llboard brd = {attacker, deffender, ep};

  if (boardhash.find(brd) != boardhash.end()) {
    return boardhash[brd];
  }

  //flag if there has been move made
  bool move_made = false;

  double best_score = DBLMIN;
  for (movetype move : ALLOWEDMOVES) {
    //get all the moves we can make of certain movetype
    ll moves = allmoves(attacker, deffender, ep, move);
    //iterate over all moves of certain movetype
    for (int i = 0; i < 64; ++i) {
      ll buff = moves & (1UL << i);
      ll new_att, new_def, new_ep;
      if (buff) {
        //move was made
        move_made = true;
        //get new positions of attacker and deffender after the move made
        get_next_position(move, buff, attacker, deffender, ep, new_att, new_def, new_ep);

        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MAXIMUM in minimizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_minimizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), cur_depth + 1, max_depth, alpha, beta);
        //update best_score and alpha
        best_score = max(best_score, bs);
        alpha = max(alpha, best_score);
        //alpha-beta cutoff
        if (beta <= alpha) {
          break;
        }
      }
    }
    //alpha-beta cutoff again
    if (beta <= alpha) {
      break;
    }
  }

  if (move_made) {
    boardhash[brd] = best_score;
    return best_score;
  } else {
    boardhash[brd] = DRAW_SCORE;
    return DRAW_SCORE; //draw; no more moves
  }

}

/* minimizing player in alphabeta algorithm */
double Minimax_Player::alphabeta_minimizing(ll attacker, ll deffender, ll ep, int cur_depth, int max_depth, double alpha, double beta) {
  if (max_depth != STARTDEPTH && (timeout() || timeout_flag_)) {
    timeout_flag_ = true;
    return -1;
  }

  depth_reached_ = depth_reached_ < cur_depth ? cur_depth : depth_reached_;

  if (cur_depth >= max_depth || has_ended(attacker, deffender)) {
    return eval(rev_bites(deffender), rev_bites(attacker), cur_depth);
  }

  //save board struct
  llboard brd = {attacker, deffender, ep};
  //check if board hash is stored
  if (boardhash.find(brd) != boardhash.end()) {
    return boardhash[brd];
  }

  //flag if there has been move made
  bool move_made = false;

  double best_score = DBLMAX;
  for (movetype move : ALLOWEDMOVES) {
    //get all the moves we can make of certain movetype
    ll moves = allmoves(attacker, deffender, ep, move);
    //iterate over all moves of certain movetype
    for (int i = 0; i < 64; ++i) {
      ll buff = moves & (1UL << i);
      ll new_att, new_def, new_ep;
      if (buff) {
        //move was made
        move_made = true;
        //get new positions of attacker and deffender after the move made
        get_next_position(move, buff, attacker, deffender, ep, new_att, new_def, new_ep);

        //after determining new attacker and deffender positions, we can go further in recursion
        //we are looking for a MINIMUM in maximizing
        //now attacker is deffender and vice versa
        double bs = alphabeta_maximizing(rev_bites(new_def), rev_bites(new_att), rev_bites(new_ep), cur_depth + 1, max_depth, alpha, beta);
        //update best_score and beta
        best_score = min(best_score, bs);
        beta = min(beta, best_score);
        //alpha-beta cutoff
        if (beta <= alpha) {
          break;
        }
      }
    }
    //alpha-beta cutoff again
    if (beta <= alpha) {
      break;
    }
  }

  if (move_made) {
    boardhash[brd] = best_score;
    return best_score;
  } else {
    boardhash[brd] = DRAW_SCORE;
    return DRAW_SCORE; //draw; no more moves
  }
}

/* General eval, calling all other evals */
double Minimax_Player::eval (ll attacker, ll deffender, int depth) {
  double e = 2.71828;
  double eval = eval_positions(attacker, deffender)/ (depth);
  return 1 / (1 + std::pow(e, -eval)); // sigmoid function
}

/* evaluates positions of pawns on board
 * points create a ratio between how far your pawns/enemy pawns got.
 */
double Minimax_Player::eval_positions(ll attacker, ll deffender) {
  double att = 0;
  double def = 0;
  int multiplier = 1;
  int rowcount = 0;
  while (attacker > 0) {
    att += (attacker & 1UL) * multiplier;
    attacker = attacker >> 1;
    if (++rowcount >= 7) {
      multiplier *= 2;
      if (multiplier == 128) {
        multiplier = 1024;
      }
      rowcount = 0;
    }
  }

  multiplier = 1024;
  rowcount = 0;
  while (deffender > 0) {
    def += (deffender & 1UL) * multiplier;
    deffender = deffender >> 1;
    if (++rowcount >= 7) {
      multiplier /= 2;
      if (multiplier == 512) {
        multiplier = 64;
      }
      rowcount = 0;
    }
  }

  return att / def;
}

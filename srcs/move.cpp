//lib includes
#include <iostream>
#include <string>

//project includes
#include "header_files/move.h"

Move::Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant, bool no_move) {
  player_ = player;
  from_ = from;
  to_ = to;
  capture_ = capture;
  en_passant_ = en_passant;
  no_move_ = no_move;
}

Move::Move() {
  player_ = none;
  from_ = std::make_pair(-1, -1);
  to_ = std::make_pair(-1, -1);
  capture_ = false;
  en_passant_ = false;
  no_move_ = true;
}

std::ostream& operator<< (std::ostream &out, Move const& move) {
  out << "From: " << char (move.get_from().second + 'A') << 8 - move.get_from().first << std::endl;
  out << "To:   " << char (move.get_to().second + 'A') << 8 - move.get_to().first;
  if (move.is_capture()) {
    out << " (capture";
    if (move.is_en_passant()) {
      out << ", en passant)";
    } else {
      out << ")";
    }
  } else if (move.is_en_passant()) {
    out << "(en passant)";
  }
  return out;
}
#ifndef MOVE_H
#define MOVE_H

//lib includes
#include <iostream>
#include <pair>

//project includes
#include "general_header.h"
#include "tile.h"

class Move {
  private:
    tile player_;
    std::pair<int, int> from_;
    std::pair<int, int> to_;
    bool capture_;
    bool en_passant_;
  public:
    Move(tile player, std::pair<int, int> from, std::pair<int, int> to, bool capture, bool en_passant);
    

}



#endif
//lib includes
#include <iostream>
#include <string>

//project includes
#include "move.h"

Move::Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant) {
	player_ = player;
	from_ = from;
	to_= to;
	capture_ = capture;
	en_passant_ = en_passant;
}

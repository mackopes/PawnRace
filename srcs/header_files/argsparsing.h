#ifndef ARGSPARSING_H
#define ARGSPARSING_H

#include <iostream>
#include <string>

#include "../../dllibs/argagg.hpp"
#include "../players/player.h"
#include "../players/benchmark_player/benchmark_player.h"
#include "../players/human_player/human_player.h"
#include "../players/minimax_player/minimax_player.h"
#include "../players/random_player/random_player.h"
#include "../players/minimax_player_experiment/minimax_player_experimental.h"

argagg::parser_results get_args(int argc, char **argv);
Player * get_player(argagg::parser_results args, std::string player);

#endif

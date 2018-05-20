#ifndef UTILITY_H
#define UTILITY_H

//lib includes
#include <bitset>
#include <algorithm>
#include <string>
#include <iostream>

//project includes
#include "general_header.h"

tile get_opposite_player(tile t);
std::bitset<64> bites(unsigned long long a);
std::string string_to_lower(std::string str);

#endif

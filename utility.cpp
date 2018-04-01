#include "utility.h"

tile get_opposite_player(tile t) {
    if (t == none || t == en_pass) {
        return none;
    } else {
        return t == black ? white : black;
    }
}

std::bitset<64> bites(unsigned long long a) {
    return std::bitset<64>(a);
}

std::string string_to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
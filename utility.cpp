#include "utility.h"

tile get_opposite_player(tile t) {
  if (t == none || t == en_pass) {
    return none;
  } else {
    return t == black ? white : black;
  }
}
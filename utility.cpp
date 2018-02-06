#include "utility.h"

tile get_opposite(tile t) {
  if (t == none) {
    return none;
  } else {
    return t == black ? white : black;
  }
}
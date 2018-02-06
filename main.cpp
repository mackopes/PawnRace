//lib includes
#include <iostream>
#include <utility>

//project includes
#include "board.h"
#include "general_header.h"

//using
using std::cout;
using std::endl;

int main() {
  Board b(4, 7);

  cout << b << endl;
  cout << endl;
  
  b.apply_move(Move(white, std::make_pair(6, 2), std::make_pair(4, 2), false, true));

  cout << b << endl;
}
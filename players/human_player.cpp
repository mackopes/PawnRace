#include "human_player.h"

#define ENUMEND captpass_l
#define ENUMSTART fwd

Human_Player :: Human_Player(tile color) : Player(color) {
  repeat_move = true;
}

Move Human_Player :: get_move(Board board) {
  std::string str;

  while (true) {
    std::cout << "Your move: ";
    std::getline(std::cin, str, '\n');

    try {
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);

      if (str.size() < 4) {
        std::cout << "Invalid input" << std::endl;
        continue;
      }

      std::pair<int, int> from = std::make_pair(8 - str[1] + '0', str[0] - 'A');
      std::pair<int, int> to = std::make_pair(8 - str[3] + '0', str[2] - 'A');


      if (board.is_empty(to.first, to.second)) {
        if (abs(str[3] - str[1]) > 1) {
          // Move(tile player, pair_ii from, pair_ii to, bool capture, bool en_passant, bool no_move = false);
          return Move(color(), from, to, false, true);
        } else {
          return Move(color(), from, to, false, false);
        }
      } else {
        if (board.is_en_pass(to.first, to.second)) {
          return Move(color(), from, to, true, true);
        } else {
          return Move(color(), from, to, true, false);
        }
      }

    } catch (const std::exception& e) {
      std::cout << "Invalid input" << std::endl;
      continue;
    }

  }
}
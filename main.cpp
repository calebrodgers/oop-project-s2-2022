#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game(704, 704, "Natural Reflection");

  game.run();

  return 0;
}

#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game(768, 768, "Natural Reflection");

  game.run();

  return 0;
}

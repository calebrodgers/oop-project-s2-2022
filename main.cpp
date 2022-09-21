#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game(640, 640, "Natural Reflection");

  game.run();

  return 0;
}

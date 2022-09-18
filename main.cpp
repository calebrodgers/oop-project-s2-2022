#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game(1000, 600, "Game");

  game.run();

  return 0;
}

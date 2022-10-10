#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game(768, 768, "Natural Reflection", "levels.nrlvl", 0, 5);

  game.run();

  return 0;
}

#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  // create game object and run the game
  Game game(768, 768, "Natural Reflection", "levels.nrlvl", "save.nrdata", 6);

  game.run();

  return 0;
}

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class GameEntity {
 protected:
  Shape* body;

 public:
  void draw(RenderWindow* window) { window->draw(*body); }
};

#endif
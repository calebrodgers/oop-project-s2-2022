#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class GameEntity {
 protected:
  Shape* body;

 public:
  void draw(RenderWindow* window) { window->draw(*body); }
  virtual Vector2f getPos() { return body->getPosition(); }
};

#endif
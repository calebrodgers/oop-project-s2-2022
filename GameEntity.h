#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

// this is the parent class for all game entities
class GameEntity {
 protected:
  // every game entity has a body
  Shape* body;

 public:
  // includes functions to draw body and get position
  void draw(RenderWindow* window) { window->draw(*body); }
  virtual Vector2f getPos() { return body->getPosition(); }
};

#endif
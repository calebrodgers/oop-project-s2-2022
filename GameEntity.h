#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

// this is the parent class for every entity in the game
class GameEntity {
 protected:
  // every entity has a body
  Shape* body;

 public:
  // this function allows game entities to be drawn in the window
  virtual void draw(RenderWindow* window) { window->draw(*body); }

  // this function returns the position of the body
  virtual Vector2f getPos() { return body->getPosition(); }
};

#endif
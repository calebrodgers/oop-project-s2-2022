#ifndef WALL_H
#define WALL_H

#include "HittableEntity.h"

// this is the class for wall squares in the game
class Wall : public HittableEntity {

 public:
 // the constructor creates the square shape and sets the color
  Wall() {
    body = new RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color{125, 21, 19});
    isHit = false;
  }

  Wall(Vector2f initialPosition) : Wall() {
    body->setPosition(initialPosition);
  }

  void hit() {
    isHit = true;
    body->setFillColor(sf::Color{201, 37, 34});
  }
};

#endif
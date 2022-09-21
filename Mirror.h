#ifndef MIRROR_H
#define MIRROR_H

#include "GameEntity.h"

class Mirror : public GameEntity {
 public:
  Mirror() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Green);
  }
  Mirror(Vector2f initialPosition) : Mirror() {
    body->setPosition(initialPosition);
  }
};

#endif
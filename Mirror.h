#ifndef MIRROR_H
#define MIRROR_H

#include "GameEntity.h"

class Mirror : public GameEntity {
 public:
  Mirror() {
    body = new sf::RectangleShape(Vector2f(60, 60));
    // body->setPosition(Vector2f(0, 0));
    body->setFillColor(sf::Color::White);
  }
  Mirror(Vector2f initialPosition) : Mirror() {
    body->setPosition(initialPosition);
  }
};

#endif
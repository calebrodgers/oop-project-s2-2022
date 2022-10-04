#ifndef TARGET_H
#define TARGET_H

#include "BorderEntity.h"

class Target : public BorderEntity {
 public:
  Target() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Yellow);
  }
  Target(Vector2f position) : Target() { body->setPosition(position); }
  void hit() {
    isHit = true;
    body->setFillColor(sf::Color::Green);
  }
};

#endif
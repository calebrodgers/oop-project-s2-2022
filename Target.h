#ifndef TARGET_H
#define TARGET_H

#include "HittableEntity.h"

class Target : public HittableEntity {
 public:
  Target() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Yellow);
    isHit = false;
  }
  Target(Vector2f position) : Target() { body->setPosition(position); }
  void hit() {
    isHit = true;
    body->setFillColor(sf::Color::Green);
  }
};

#endif
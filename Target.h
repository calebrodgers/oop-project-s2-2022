#ifndef TARGET_H
#define TARGET_H

#include "HittableEntity.h"

// this is the class for the target in the levels
class Target : public HittableEntity {
 public:
  // constructor creates square shape, and sets colour
  Target() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Yellow);
    isHit = false;
  }

  Target(Vector2f position) : Target() { body->setPosition(position); }

  // when hit by light, change hit variable and turn green
  void hit() {
    isHit = true;
    body->setFillColor(sf::Color::Green);
  }
};

#endif
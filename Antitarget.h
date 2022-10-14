#ifndef ANTITARGET_H
#define ANTITARGET_H

#include "BorderEntity.h"

class Antitarget : public BorderEntity {
 public:
  Antitarget() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color(180, 0, 255));
    isHit = false;
  }

  Antitarget(Vector2f position) : Antitarget() { body->setPosition(position); }

  void hit() {
    isHit = true;
    body->setFillColor(sf::Color::Black);
  }
};

#endif
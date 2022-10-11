#ifndef ANTITARGET_H
#define ANTITARGET_H

#include "GameEntity.h"

class Antitarget : public GameEntity {
 public:
  Antitarget() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color(255, 0, 255));
  }
  Antitarget(Vector2f position) : Antitarget() { body->setPosition(position); }
};

#endif
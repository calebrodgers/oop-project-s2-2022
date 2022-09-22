#ifndef EMITTER_H
#define EMITTER_H

#include "BorderEntity.h"

class Emitter : public BorderEntity {
 public:
  Emitter() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Red);
  }
  Emitter(Vector2f position) : Emitter() { body->setPosition(position); }
};

#endif
#ifndef EMITTER_H
#define EMITTER_H

#include "HittableEntity.h"
#include "Light.h"

class Emitter : public GameEntity {
 private:
  Vector2f lightInitialVelocity;
  int countLight;

 public:
  Emitter() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Red);
    countLight = 0;
  }

  Emitter(Vector2f position, int winSize) : Emitter() {
    body->setPosition(position);
    if (position.y == 0) {
      lightInitialVelocity = Vector2f(0, 64);
    } else if (position.y == winSize) {
      lightInitialVelocity = Vector2f(0, -64);
    } else if (position.x == 0) {
      lightInitialVelocity = Vector2f(64, 0);
    } else if (position.x == winSize) {
      lightInitialVelocity = Vector2f(-64, 0);
    }
  }

  Vector2f getPos() { return body->getPosition(); }
  Vector2f getInitialVelocity() { return lightInitialVelocity; }
};

#endif
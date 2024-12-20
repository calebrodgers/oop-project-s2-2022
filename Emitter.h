#ifndef EMITTER_H
#define EMITTER_H

#include "HittableEntity.h"
#include "Light.h"

// this is the class for the object in the game that emits the beam of light
class Emitter : public GameEntity {
 private:
  Vector2f lightInitialVelocity;

 public:
  // constructor initializes rectange shape and colours it red
  Emitter() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Red);
  }

  // this constructor sets the position and determines initial light direction
  Emitter(Vector2f position, int winSize) : Emitter() {
    body->setPosition(position);
    // the initial velocity of the light is determined by which edge the emitter
    // is located on
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

  Vector2f getInitialVelocity() { return lightInitialVelocity; }
};

#endif
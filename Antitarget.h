#ifndef ANTITARGET_H
#define ANTITARGET_H

#include "HittableEntity.h"

// this is the class for antitargets in the game (the blocks that the player has to avoid hitting with light beam)
class Antitarget : public HittableEntity {
 public:
  // constructor initializes shapes and sets hit variable to false
  Antitarget() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color(180, 0, 255));
    isHit = false;
  }

  Antitarget(Vector2f position) : Antitarget() { body->setPosition(position); }

  // when the antitarget is hit it turns black
  void hit() {
    isHit = true;
    body->setFillColor(sf::Color::Black);
  }
};

#endif
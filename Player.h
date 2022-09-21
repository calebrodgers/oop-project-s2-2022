#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "GameEntity.h"

class Player : public GameEntity {
 public:
  Player() {
    body = new sf::CircleShape(32.f);
    body->setFillColor(sf::Color::White);
    std::cout << "Mirror made";
  }

  void move(Vector2f amnt) { body->move(amnt); }
};

#endif
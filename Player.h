#ifndef PLAYER_H
#define PLAYER_H

#include "BorderWall.h"
#include "GameEntity.h"

class Player : public GameEntity {
 public:
  Player() {
    body = new sf::CircleShape(32.f);
    body->setPosition(Vector2f(128, 128));
    body->setFillColor(sf::Color::Blue);
  }

  void move(Vector2f amnt, int winSize) {
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(-amnt);
    }
  }
};

#endif
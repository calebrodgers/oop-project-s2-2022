#ifndef PLAYER_H
#define PLAYER_H

#include "BorderWall.h"
#include "GameEntity.h"
#include "Mirror.h"

class Player : public GameEntity {
 public:
  Player() {
    body = new sf::CircleShape(32.f);
    body->setPosition(Vector2f(128, 128));
    body->setFillColor(sf::Color::Blue);
  }

  void move(Vector2f amnt, int winSize, Mirror* mirror) {
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
    } else if (x == mirror->getPos().x && y == mirror->getPos().y){
      if (mirror->move(amnt, winSize) == false) {
        body->move(Vector2f(-amnt.x, -amnt.y));
      }
    }
  }
};

#endif
#ifndef MIRROR_H
#define MIRROR_H

#include "GameEntity.h"

class Mirror : public GameEntity {
 public:
  Mirror() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Green);
  }
  Mirror(Vector2f initialPosition) : Mirror() {
    body->setPosition(initialPosition);
  }

  Vector2f getPos() { return body->getPosition(); }

  bool move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors) {
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;

    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
      return false;
    }

    int mirrorCount = 0;
    for (int i = 0; i < numOfMirrors; i++) {
      if (body->getPosition() == mirrors[i]->getPos()) {
        mirrorCount++;
      }
    }
    if (mirrorCount > 1) {
      body->move(Vector2f(-amnt.x, -amnt.y));
      return false;
    }
    return true;
  }
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "BorderWall.h"
#include "GameEntity.h"
#include "Mirror.h"

class Player : public GameEntity {
 private:
  bool wasWPressed = false;
  bool wasAPressed = false;
  bool wasSPressed = false;
  bool wasDPressed = false;

 public:
  Player() {
    body = new sf::CircleShape(32.f);
    body->setPosition(Vector2f(64, 64));
    body->setFillColor(sf::Color::Blue);
  }

  Player(Vector2f spawnPoint) : Player() { body->setPosition(spawnPoint); }

  void move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors) {
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
    }

    for (int i = 0; i < numOfMirrors; i++) {
      if (x == mirrors[i]->getPos().x && y == mirrors[i]->getPos().y) {
        if (mirrors[i]->move(amnt, winSize, numOfMirrors, mirrors, -1) ==
            false) {
          body->move(Vector2f(-amnt.x, -amnt.y));
        }
      }
    }
  }

  void update(int numOfMirrors, Mirror** mirrors) {
    if (!wasWPressed) {
      if (Keyboard::isKeyPressed(Keyboard::W)) {
        move(Vector2f(0, -64), 768, numOfMirrors, mirrors);
        wasWPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::W)) {
      wasWPressed = false;
    }

    if (!wasAPressed) {
      if (Keyboard::isKeyPressed(Keyboard::A)) {
        move(Vector2f(-64, 0), 768, numOfMirrors, mirrors);
        wasAPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::A)) {
      wasAPressed = false;
    }

    if (!wasSPressed) {
      if (Keyboard::isKeyPressed(Keyboard::S)) {
        move(Vector2f(0, 64), 768, numOfMirrors, mirrors);
        wasSPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::S)) {
      wasSPressed = false;
    }

    if (!wasDPressed) {
      if (Keyboard::isKeyPressed(Keyboard::D)) {
        move(Vector2f(64, 0), 768, numOfMirrors, mirrors);
        wasDPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::D)) {
      wasDPressed = false;
    }
  }

  Vector2f getPos() { return body->getPosition(); }
};

#endif
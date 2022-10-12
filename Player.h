#ifndef PLAYER_H
#define PLAYER_H

#include "Antitarget.h"
#include "BorderWall.h"
#include "GameEntity.h"
#include "Mirror.h"
#include "Wall.h"

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

  void move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors,
            Wall** walls, int numOfWalls, Antitarget** antitargets,
            int numOfAntitargets) {
    Vector2f initialPos = body->getPosition();
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
    }

    for (int i = 0; i < numOfMirrors; i++) {
      if (x == mirrors[i]->getPos().x && y == mirrors[i]->getPos().y) {
        if (mirrors[i]->move(amnt, winSize, numOfMirrors, mirrors, -1, walls,
                             numOfWalls) == false) {
          body->move(Vector2f(-amnt.x, -amnt.y));
        }
      }
    }

    for (int i = 0; i < numOfWalls; i++) {
      if (x == walls[i]->getPos().x && y == walls[i]->getPos().y) {
        body->move(Vector2f(-amnt.x, -amnt.y));
      }
    }

    for (int i = 0; i < numOfAntitargets; i++) {
      if (x == antitargets[i]->getPos().x && y == antitargets[i]->getPos().y &&
          body->getPosition() != initialPos) {
        body->move(Vector2f(-amnt.x, -amnt.y));
      }
    }
  }

  void update(int numOfMirrors, Mirror** mirrors, Wall** walls, int numOfWalls,
              Antitarget** antitargets, int numOfAntitargets) {
    if (!wasWPressed) {
      if (Keyboard::isKeyPressed(Keyboard::W) ||
          Keyboard::isKeyPressed(Keyboard::Up)) {
        move(Vector2f(0, -64), 768, numOfMirrors, mirrors, walls, numOfWalls,
             antitargets, numOfAntitargets);
        wasWPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::W) &&
               !Keyboard::isKeyPressed(Keyboard::Up)) {
      wasWPressed = false;
    }

    if (!wasAPressed) {
      if (Keyboard::isKeyPressed(Keyboard::A) ||
          Keyboard::isKeyPressed(Keyboard::Left)) {
        move(Vector2f(-64, 0), 768, numOfMirrors, mirrors, walls, numOfWalls,
             antitargets, numOfAntitargets);
        wasAPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::A) &&
               !Keyboard::isKeyPressed(Keyboard::Left)) {
      wasAPressed = false;
    }

    if (!wasSPressed) {
      if (Keyboard::isKeyPressed(Keyboard::S) ||
          Keyboard::isKeyPressed(Keyboard::Down)) {
        move(Vector2f(0, 64), 768, numOfMirrors, mirrors, walls, numOfWalls,
             antitargets, numOfAntitargets);
        wasSPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::S) &&
               !Keyboard::isKeyPressed(Keyboard::Down)) {
      wasSPressed = false;
    }

    if (!wasDPressed) {
      if (Keyboard::isKeyPressed(Keyboard::D) ||
          Keyboard::isKeyPressed(Keyboard::Right)) {
        move(Vector2f(64, 0), 768, numOfMirrors, mirrors, walls, numOfWalls,
             antitargets, numOfAntitargets);
        wasDPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::D) &&
               !Keyboard::isKeyPressed(Keyboard::Right)) {
      wasDPressed = false;
    }
  }

  Vector2f getPos() { return body->getPosition(); }
};

#endif
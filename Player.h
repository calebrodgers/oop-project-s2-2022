#ifndef PLAYER_H
#define PLAYER_H

#include "BorderWall.h"
#include "GameEntity.h"
#include "Mirror.h"
#include "Wall.h"

// this is the class for the player in the game
class Player : public GameEntity {
 private:
  bool wasWPressed = false;
  bool wasAPressed = false;
  bool wasSPressed = false;
  bool wasDPressed = false;

 public:
  // constructor creates the circle body for player and sets colour
  Player() {
    body = new sf::CircleShape(32.f);
    body->setPosition(Vector2f(64, 64));
    body->setFillColor(sf::Color::Blue);
  }

  Player(Vector2f spawnPoint) : Player() { body->setPosition(spawnPoint); }

  // moving the player
  void move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors, Wall** walls, int numOfWalls) {
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;
    // dont let the player move into the border
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
    }

    // attempt to push mirror, but if it fails dont let player move
    for (int i = 0; i < numOfMirrors; i++) {
      if (x == mirrors[i]->getPos().x && y == mirrors[i]->getPos().y) {
        if (mirrors[i]->move(amnt, winSize, numOfMirrors, mirrors, -1, walls, numOfWalls) ==
            false) {
          body->move(Vector2f(-amnt.x, -amnt.y));
        }
      }
    }

    // dont let player move into walls
    for (int i = 0; i < numOfWalls; i++) {
      if (x == walls[i]->getPos().x && y == walls[i]->getPos().y) {
        body->move(Vector2f(-amnt.x, -amnt.y));
      }
    }
  }

  // update player movement based on pressed keys
  void update(int numOfMirrors, Mirror** mirrors, Wall** walls, int numOfWalls) {
    if (!wasWPressed) {
      // move up
      if (Keyboard::isKeyPressed(Keyboard::W)) {
        move(Vector2f(0, -64), 768, numOfMirrors, mirrors, walls, numOfWalls);
        wasWPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::W)) {
      wasWPressed = false;
    }

    // move left
    if (!wasAPressed) {
      if (Keyboard::isKeyPressed(Keyboard::A)) {
        move(Vector2f(-64, 0), 768, numOfMirrors, mirrors, walls, numOfWalls);
        wasAPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::A)) {
      wasAPressed = false;
    }

    // move down
    if (!wasSPressed) {
      if (Keyboard::isKeyPressed(Keyboard::S)) {
        move(Vector2f(0, 64), 768, numOfMirrors, mirrors, walls, numOfWalls);
        wasSPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::S)) {
      wasSPressed = false;
    }

    // move right
    if (!wasDPressed) {
      if (Keyboard::isKeyPressed(Keyboard::D)) {
        move(Vector2f(64, 0), 768, numOfMirrors, mirrors, walls, numOfWalls);
        wasDPressed = true;
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::D)) {
      wasDPressed = false;
    }
  }

  Vector2f getPos() { return body->getPosition(); }
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "Antitarget.h"
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
  bool moved = false;
  int step_count = 0;
  Texture texture;

 public:
  // constructor creates the circle body for player and sets colour
  Player() {
    body = new sf::RectangleShape(Vector2f(64, 96));
    body->setOrigin(0, 32);
    body->setPosition(Vector2f(64, 64));

    texture.loadFromFile("scientist_sprite.png");
    body->setTexture(&texture);
    body->setTextureRect(IntRect(0, 0, 64, 96));
  }

  Player(Vector2f spawnPoint) : Player() { body->setPosition(spawnPoint); }

  // moving the player
  bool move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors,
            Wall** walls, int numOfWalls, Antitarget** antitargets,
            int numOfAntitargets) {
    Vector2f initialPos = body->getPosition();
    body->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;

    // dont let the player move into the border
    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
      return false;
    }

    // attempt to push mirror, but if it fails dont let player move
    for (int i = 0; i < numOfMirrors; i++) {
      if (x == mirrors[i]->getPos().x && y == mirrors[i]->getPos().y) {
        if (mirrors[i]->move(amnt, winSize, numOfMirrors, mirrors, -1, walls,
                             numOfWalls) == false) {
          body->move(Vector2f(-amnt.x, -amnt.y));
          return false;
        }
      }
    }

    // dont let player move into walls
    for (int i = 0; i < numOfWalls; i++) {
      if (x == walls[i]->getPos().x && y == walls[i]->getPos().y) {
        body->move(Vector2f(-amnt.x, -amnt.y));
        return false;
      }
    }

    // dont let player move into antitarget
    for (int i = 0; i < numOfAntitargets; i++) {
      if (x == antitargets[i]->getPos().x && y == antitargets[i]->getPos().y &&
          body->getPosition() != initialPos) {
        body->move(Vector2f(-amnt.x, -amnt.y));
        return false;
      }
    }
    return true;
  }

  // update player movement based on pressed keys
  void update(int numOfMirrors, Mirror** mirrors, Wall** walls, int numOfWalls,
              Antitarget** antitargets, int numOfAntitargets) {
    // move up
    if (!wasWPressed) {
      if (Keyboard::isKeyPressed(Keyboard::W) ||
          Keyboard::isKeyPressed(Keyboard::Up)) {
        bool moved = move(Vector2f(0, -64), 768, numOfMirrors, mirrors, walls,
                          numOfWalls, antitargets, numOfAntitargets);
        wasWPressed = true;
        body->setTextureRect(IntRect(0, 288, 64, 96));
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::W) &&
               !Keyboard::isKeyPressed(Keyboard::Up)) {
      wasWPressed = false;
    }

    // move left
    if (!wasAPressed) {
      if (Keyboard::isKeyPressed(Keyboard::A) ||
          Keyboard::isKeyPressed(Keyboard::Left)) {
        bool moved = move(Vector2f(-64, 0), 768, numOfMirrors, mirrors, walls,
                          numOfWalls, antitargets, numOfAntitargets);
        wasAPressed = true;
        body->setTextureRect(IntRect(0, 96, 64, 96));
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::A) &&
               !Keyboard::isKeyPressed(Keyboard::Left)) {
      wasAPressed = false;
    }

    // move down
    if (!wasSPressed) {
      if (Keyboard::isKeyPressed(Keyboard::S) ||
          Keyboard::isKeyPressed(Keyboard::Down)) {
        bool moved = move(Vector2f(0, 64), 768, numOfMirrors, mirrors, walls,
                          numOfWalls, antitargets, numOfAntitargets);
        wasSPressed = true;
        body->setTextureRect(IntRect(0, 0, 64, 96));
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::S) &&
               !Keyboard::isKeyPressed(Keyboard::Down)) {
      wasSPressed = false;
    }

    // move right
    if (!wasDPressed) {
      if (Keyboard::isKeyPressed(Keyboard::D) ||
          Keyboard::isKeyPressed(Keyboard::Right)) {
        bool moved = move(Vector2f(64, 0), 768, numOfMirrors, mirrors, walls,
                          numOfWalls, antitargets, numOfAntitargets);
        wasDPressed = true;
        body->setTextureRect(IntRect(0, 192, 64, 96));
      }
    } else if (!Keyboard::isKeyPressed(Keyboard::D) &&
               !Keyboard::isKeyPressed(Keyboard::Right)) {
      wasDPressed = false;
    }
  }
};

#endif
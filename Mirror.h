#ifndef MIRROR_H
#define MIRROR_H

#include "GameEntity.h"
#include "Wall.h"

// definition of mirrors in game
class Mirror : public GameEntity {
 private:
  // have direction and an additional triangle shape
  char direction;
  ConvexShape* triangle;

 public:
  // default constructor initialises square shape  
  Mirror() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color::Cyan);
  }
  Mirror(Vector2f initialPosition, char _direction) : Mirror() {
    body->setPosition(initialPosition);
    direction = _direction;
    triangle = new sf::ConvexShape;
    triangle->setPointCount(3);
    direction = _direction;
    switch (direction) {
      case 'N':
        triangle->setPoint(0, Vector2f(0, 0));
        triangle->setPoint(1, Vector2f(0, 64));
        triangle->setPoint(2, Vector2f(64, 64));
        break;
      case 'E':
        triangle->setPoint(0, Vector2f(0, 0));
        triangle->setPoint(1, Vector2f(0, 64));
        triangle->setPoint(2, Vector2f(64, 0));
        break;
      case 'S':
        triangle->setPoint(0, Vector2f(0, 0));
        triangle->setPoint(1, Vector2f(64, 64));
        triangle->setPoint(2, Vector2f(64, 0));
        break;
      case 'W':
        triangle->setPoint(0, Vector2f(0, 64));
        triangle->setPoint(1, Vector2f(64, 64));
        triangle->setPoint(2, Vector2f(64, 0));
        break;
    }
    triangle->setFillColor(sf::Color(230, 230, 230));
    triangle->setPosition(initialPosition);
  }

  Vector2f getPos() { return body->getPosition(); }

  bool move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors,
            int nextSkip, Wall** walls, int numOfWalls) {
    int skipMirror = 0;
    for (int i = 0; i < numOfMirrors; i++) {
      if (body->getPosition() == mirrors[i]->getPos() && i != nextSkip) {
        skipMirror = i;
      }
    }

    body->move(amnt);
    triangle->move(amnt);
    float x = body->getPosition().x;
    float y = body->getPosition().y;

    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
      triangle->move(Vector2f(-amnt.x, -amnt.y));
      return false;
    }

    int mirrorCount = 0;
    int checkMirror = 0;
    for (int i = 0; i < numOfMirrors; i++) {
      if (body->getPosition() == mirrors[i]->getPos() && i != skipMirror) {
        mirrorCount = 1;
        checkMirror = i;
      }
    }
    if (mirrorCount == 1) {
      if (mirrors[checkMirror]->move(amnt, winSize, numOfMirrors, mirrors,
                                     skipMirror, walls, numOfWalls) == false) {
        body->move(Vector2f(-amnt.x, -amnt.y));
        triangle->move(Vector2f(-amnt.x, -amnt.y));
        return false;
      }
    }

    // detect if mirror is trying to move into a wall block
    for (int i = 0; i < numOfWalls; i++) {
      if (body->getPosition() == walls[i]->getPos()) {
        body->move(Vector2f(-amnt.x, -amnt.y));
        triangle->move(Vector2f(-amnt.x, -amnt.y));
        return false;
      }
    }

    return true;
  }

  // requires unique draw function as the mirror is composed of two different shapes
  void draw(RenderWindow* window) {
    window->draw(*body);
    window->draw(*triangle);
  }

  char getDirection() { return direction; };
};

#endif
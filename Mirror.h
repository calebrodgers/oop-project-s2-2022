#ifndef MIRROR_H
#define MIRROR_H

#include "GameEntity.h"
#include "Wall.h"

class Mirror : public GameEntity {
 private:
  char direction;
  ConvexShape* triangle;

 public:
  Mirror() {
    body = new sf::RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color(210, 180, 140));
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
    triangle->setFillColor(sf::Color(200, 200, 200));
    triangle->setPosition(initialPosition);
  }

  Vector2f getPos() { return triangle->getPosition(); }

  bool move(Vector2f amnt, int winSize, int numOfMirrors, Mirror** mirrors,
            int nextSkip, Wall** walls, int numOfWalls) {
    int skipMirror = 0;
    for (int i = 0; i < numOfMirrors; i++) {
      if (triangle->getPosition() == mirrors[i]->getPos() && i != nextSkip) {
        skipMirror = i;
      }
    }

    body->move(amnt);
    triangle->move(amnt);
    float x = triangle->getPosition().x;
    float y = triangle->getPosition().y;

    if (x == 0 || y == 0 || x == winSize - 64 || y == winSize - 64) {
      body->move(Vector2f(-amnt.x, -amnt.y));
      triangle->move(Vector2f(-amnt.x, -amnt.y));
      return false;
    }

    int mirrorCount = 0;
    int checkMirror = 0;
    for (int i = 0; i < numOfMirrors; i++) {
      if (triangle->getPosition() == mirrors[i]->getPos() && i != skipMirror) {
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
      if (triangle->getPosition() == walls[i]->getPos()) {
        body->move(Vector2f(-amnt.x, -amnt.y));
        triangle->move(Vector2f(-amnt.x, -amnt.y));
        return false;
      }
    }

    return true;
  }

  void draw(RenderWindow* window) { window->draw(*triangle); }

  void drawBase(RenderWindow* window) { window->draw(*body); }

  char getDirection() { return direction; };
};

#endif
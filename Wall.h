#ifndef WALL_H
#define WALL_H

#include "HittableEntity.h"

class Wall : public HittableEntity {
 private:
  int x;

 public:
  Wall() {
    body = new RectangleShape(Vector2f(64, 64));
    body->setFillColor(sf::Color{125, 21, 19});
    isHit = false;
  }

  Wall(Vector2f initialPosition) : Wall() {
    body->setPosition(initialPosition);
  }

  void hit() {
    isHit = true;
    body->setFillColor(sf::Color{201, 37, 34});
  }

  void draw(RenderWindow* window) {
    window->draw(*body);
    body->setFillColor(sf::Color{125, 21, 19});
  }
};

#endif
#ifndef BORDERWALL_H
#define BORDERWALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

// this is the class for the border wall around each level
class BorderWall {
 private:
  Shape** body;

 public:
  BorderWall(int winSize) {
    // when the borderwall is initialized, 4 rectangles are created, one for
    // each edge of the screen
    body = new Shape*[4];
    body[0] = new RectangleShape(Vector2f(winSize, 64));

    body[1] = new RectangleShape(Vector2f(64, winSize));

    body[2] = new RectangleShape(Vector2f(winSize, 64));
    body[2]->setPosition(Vector2f(0, winSize - 64));

    body[3] = new RectangleShape(Vector2f(64, winSize));
    body[3]->setPosition(Vector2f(winSize - 64, 0));

    for (int i = 0; i < 4; i++) {
      body[i]->setFillColor(Color::Black);
    }
  }

  // the borderwall requires a unique draw function as it is composed of 4
  // shapes
  void draw(RenderWindow* window) {
    for (int i = 0; i < 4; i++) {
      window->draw(*body[i]);
    }
  }
};

#endif
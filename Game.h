#ifndef GAME_H
#define GAME_h

#include <SFML/Graphics.hpp>

#include "GameEntity.h"
#include "Mirror.h"
#include "Player.h"

class Game {
 private:
  sf::RenderWindow* window;
  Player* pyr;
  Mirror* mir1;
  Mirror* mir2;

 public:
  Game(int size_x, int size_y, std::string window_name) {
    window = new sf::RenderWindow(VideoMode(size_x, size_y), window_name);
  }

  void run() {
    mir1 = new Mirror(Vector2f(60, 60));
    mir2 = new Mirror(Vector2f(480, 180));
    pyr = new Player();

    bool wasWPressed = false;
    bool wasAPressed = false;
    bool wasSPressed = false;
    bool wasDPressed = false;

    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
      }

      if (!wasWPressed) {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
          pyr->move(Vector2f(0, -60));
          wasWPressed = true;
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::W)) {
        wasWPressed = false;
      }

      if (!wasAPressed) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
          pyr->move(Vector2f(-60, 0));
          wasAPressed = true;
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::A)) {
        wasAPressed = false;
      }

      if (!wasSPressed) {
        if (Keyboard::isKeyPressed(Keyboard::S)) {
          pyr->move(Vector2f(0, 60));
          wasSPressed = true;
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::S)) {
        wasSPressed = false;
      }

      if (!wasDPressed) {
        if (Keyboard::isKeyPressed(Keyboard::D)) {
          pyr->move(Vector2f(60, 0));
          wasDPressed = true;
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::D)) {
        wasDPressed = false;
      }

      window->clear();

      mir1->draw(window);
      mir2->draw(window);
      pyr->draw(window);

      window->display();
    }
  }
};

#endif
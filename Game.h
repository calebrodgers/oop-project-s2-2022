#ifndef GAME_H
#define GAME_h

#include <SFML/Graphics.hpp>

#include "GameEntity.h"

using namespace sf;

class Game {
 private:
  RenderWindow* window;

 public:
  Game(int size_x, int size_y, std::string window_name) {
    window = new RenderWindow(VideoMode(size_x, size_y), window_name);
  }

  void run() {
    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
      }

      window->clear();
      window->display();
    }
  }
};

#endif
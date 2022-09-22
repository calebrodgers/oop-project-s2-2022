#ifndef GAME_H
#define GAME_h

#include <SFML/Graphics.hpp>

#include "BorderWall.h"
#include "GameEntity.h"
#include "Level.h"

class Game {
 private:
  sf::RenderWindow* window;
  int currentLevel;
  int totalLevels;
  Level** levels;
  bool wasLPressed = false;

 public:
  Game(int size_x, int size_y, std::string window_name) {
    window = new sf::RenderWindow(VideoMode(size_x, size_y), window_name);
  }

  void run() {
    currentLevel = 0;
    totalLevels = 3;
    levels = new Level*[totalLevels];
    levels[currentLevel] = new Level("levels.nrlvl", currentLevel);

    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
      }

      if (!wasLPressed) {
        if (Keyboard::isKeyPressed(Keyboard::L)) {
          wasLPressed = true;
          if (currentLevel != totalLevels - 1) {
            levels[currentLevel + 1] =
                new Level("levels.nrlvl", currentLevel + 1);
            currentLevel++;
          }
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::L)) {
        wasLPressed = false;
      }

      // Clear Window
      window->clear(sf::Color::White);

      levels[currentLevel]->updateAndDraw(window);

      // Display Window
      window->display();
    }
  }
};

#endif
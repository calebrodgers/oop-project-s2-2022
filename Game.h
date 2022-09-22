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
  int numOfLevels;
  Level** levels;
  bool wasLPressed = false;

 public:
  Game(int size_x, int size_y, std::string window_name, std::string levelsFile,
       int startLevel, int numOfLevels) {
    window = new sf::RenderWindow(VideoMode(size_x, size_y), window_name);
    this->currentLevel = startLevel;
    this->numOfLevels = numOfLevels;
    levels = new Level*[numOfLevels];
    levels[currentLevel] = new Level(levelsFile, currentLevel);
  }

  void run() {
    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
      }

      if (!wasLPressed) {
        if (Keyboard::isKeyPressed(Keyboard::L)) {
          wasLPressed = true;
          if (currentLevel != numOfLevels - 1) {
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
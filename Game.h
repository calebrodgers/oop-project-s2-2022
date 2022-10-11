#ifndef GAME_H
#define GAME_h

#include <SFML/Graphics.hpp>
#include <string>

#include "BorderWall.h"
#include "Cutscene.h"
#include "GameEntity.h"
#include "Level.h"
#include "Scoreboard.h"

class Game {
 private:
  sf::RenderWindow* window;
  int currentLevel;
  int numOfLevels;
  Level** levels;
  Scoreboard* scoreboard;
  Cutscene* cutscene;
  bool wasRPressed = false;
  std::string message;

 public:
  Game(int size_x, int size_y, std::string window_name, std::string levelsFile,
       int startLevel, int numOfLevels) {
    window = new sf::RenderWindow(VideoMode(size_x, size_y), window_name);
    this->currentLevel = startLevel;
    this->numOfLevels = numOfLevels;
    levels = new Level*[numOfLevels];
    levels[currentLevel] = new Level(levelsFile, currentLevel);
    scoreboard = new Scoreboard(Vector2f(10, 2));
  }

  void run() {
    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
      }

      if (levels[currentLevel]->isDone()) {
        window->clear(sf::Color::White);
        levels[currentLevel]->updateAndDraw(window);
        window->display();
        message = "LEVEL ";
        message.append(std::to_string(currentLevel + 1));
        message.append(" COMPLETE");
        cutscene = new Cutscene(message, levels[currentLevel]->isDone());
        cutscene->run(window, true);
        delete cutscene;

        if (currentLevel != numOfLevels - 1) {
          levels[currentLevel + 1] =
              new Level("levels.nrlvl", currentLevel + 1);
          currentLevel++;
        }
      }

      if (levels[currentLevel]->needsReset()) {
        window->clear(sf::Color::White);
        levels[currentLevel]->updateAndDraw(window);
        window->display();
        message = "LEVEL FAILED";
        cutscene = new Cutscene(message, levels[currentLevel]->isDone());
        cutscene->run(window, levels[currentLevel]->isDone());
        delete cutscene;

        levels[currentLevel] = new Level("levels.nrlvl", currentLevel);
      }

      if (!wasRPressed) {
        if (Keyboard::isKeyPressed(Keyboard::R)) {
          wasRPressed = true;

          window->clear(sf::Color::White);
          levels[currentLevel]->updateAndDraw(window);
          window->display();
          message = "RESETTING LEVEL";
          cutscene = new Cutscene(message, levels[currentLevel]->isDone());
          cutscene->run(window, levels[currentLevel]->isDone());
          delete cutscene;

          levels[currentLevel] = new Level("levels.nrlvl", currentLevel);
        }
      } else if (!Keyboard::isKeyPressed(Keyboard::R)) {
        wasRPressed = false;
      }

      // Clear Window
      window->clear(sf::Color::White);

      levels[currentLevel]->updateAndDraw(window);
      scoreboard->updateAndDraw(currentLevel + 1, window);

      // Display Window
      window->display();
    }
  }
};

#endif
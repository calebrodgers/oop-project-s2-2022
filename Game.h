#ifndef GAME_H
#define GAME_h

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "BorderWall.h"
#include "Cutscene.h"
#include "GameEntity.h"
#include "Level.h"
#include "Scoreboard.h"
#include "TutorialText.h"

class Game {
 private:
  sf::RenderWindow* window;
  int currentLevel;
  int numOfLevels;
  int loopCount;
  Level** levels;
  Scoreboard* scoreboard;
  Cutscene* cutscene;
  TutorialText* tutorialText;
  bool wasRPressed = false;
  std::string message;
  std::fstream saveFile;
  std::string saveFilePath;

 public:
  Game(int size_x, int size_y, std::string window_name,
       std::string levelsFilePath, std::string saveFilePath, int numOfLevels) {
    window = new sf::RenderWindow(VideoMode(size_x, size_y), window_name);
    this->saveFilePath = saveFilePath;
    saveFile.open(saveFilePath);
    char levelChar;
    saveFile.get(levelChar);
    saveFile.close();
    this->currentLevel = levelChar - '0';
    this->numOfLevels = numOfLevels;
    levels = new Level*[numOfLevels];
    levels[currentLevel] = new Level(levelsFilePath, currentLevel);
    scoreboard = new Scoreboard(Vector2f(10, 2));
    loopCount = 0;
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
        scoreboard->updateAndDraw(currentLevel + 1, window);
        window->display();
        loopCount = 0;

        if (currentLevel != numOfLevels - 1) {
          message = "LEVEL ";
          message.append(std::to_string(currentLevel + 1));
          message.append(" COMPLETE");
          cutscene = new Cutscene(message, levels[currentLevel]->isDone());
          cutscene->run(window, levels[currentLevel]->isDone(), true);
          delete cutscene;
          levels[currentLevel + 1] =
              new Level("levels.nrlvl", currentLevel + 1);
          currentLevel++;
          saveFile.open(saveFilePath);
          saveFile.put(currentLevel + 48);
          saveFile.close();
        } else {
          message = "GAME COMPLETE!";
          cutscene = new Cutscene(message, levels[currentLevel]->isDone());
          cutscene->run(window, levels[currentLevel]->isDone(), true);
          saveFile.open(saveFilePath);
          saveFile.put(48);
          saveFile.close();
          return;
        }
      }

      if (levels[currentLevel]->needsReset()) {
        window->clear(sf::Color::White);
        levels[currentLevel]->updateAndDraw(window);
        scoreboard->updateAndDraw(currentLevel + 1, window);
        window->display();
        message = "LEVEL FAILED";
        cutscene = new Cutscene(message, levels[currentLevel]->isDone());
        cutscene->run(window, levels[currentLevel]->isDone(), true);
        delete cutscene;
        loopCount = 0;

        levels[currentLevel] = new Level("levels.nrlvl", currentLevel);
      }

      if (!wasRPressed) {
        if (Keyboard::isKeyPressed(Keyboard::R)) {
          wasRPressed = true;

          window->clear(sf::Color::White);
          levels[currentLevel]->updateAndDraw(window);
          scoreboard->updateAndDraw(currentLevel + 1, window);
          window->display();
          message = "RESETTING LEVEL";
          cutscene = new Cutscene(message, levels[currentLevel]->isDone());
          cutscene->run(window, levels[currentLevel]->isDone(), false);
          delete cutscene;
          loopCount = 0;

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

      if (currentLevel < 4 && loopCount < 6) {
        tutorialText = new TutorialText(window, currentLevel, loopCount);
        loopCount++;
      }
    }
  }
};

#endif
